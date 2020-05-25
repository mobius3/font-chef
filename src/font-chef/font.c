#include "font-chef/font.h"
#include "stb_truetype.h"
#include "utf8-decode.h"
#include "font-internal.h"
#include <math.h>
#include <font-chef/character-mapping.h>


#define fc_fabs(x) ((float) fabs((double) x))

struct fc_font * fc_construct(
    uint8_t const * font_data,
    struct fc_font_size font_size,
    struct fc_color font_color
) {
  struct fc_font * font = malloc(sizeof(*font));
  font->metadata.font_data = font_data;
  font->metadata.size = font_size;
  font->metadata.color = font_color;
  font->metadata.info = malloc(sizeof(stbtt_fontinfo));

  font->pixels.data = NULL;
  font->pixels.dimensions.width = font->pixels.dimensions.height = .0f;

  font->packing.count = 0;
  font->packing.blocks = malloc(sizeof(*font->packing.blocks) * 8);
  font->packing.capacity = 8;

  font->metrics.ascent = font->metrics.descent = font->metrics.line_gap = 0;
  font->metrics.scale = 0;

  stbtt_InitFont(font->metadata.info, font->metadata.font_data, 0);

  return font;
}

void fc_add(struct fc_font * font, uint32_t first, uint32_t last) {
  /* handles the case when more memory needed to add block*/
  if (font->packing.count >= font->packing.capacity) {
    size_t new_capacity = font->packing.capacity * 2;
    font->packing.blocks = realloc(font->packing.blocks, sizeof(*font->packing.blocks) * new_capacity);
    font->packing.capacity = new_capacity;
    /* TODO: handle and return out-of-memory */
  }

  float size = font->metadata.size.value;
  if (font->metadata.size.type == fc_size_type__pt)
    size = STBTT_POINT_SIZE(size);
  size_t char_count_in_block;
  size_t block_count = font->packing.count;
  size_t i = block_count;
  char_count_in_block = last - first +1;
  font->packing.blocks[i].first_unicode_codepoint_in_range = first;
  font->packing.blocks[i].num_chars = (int) char_count_in_block;
  font->packing.blocks[i].font_size = size;
  font->packing.blocks[i].array_of_unicode_codepoints = NULL;
  font->packing.blocks[i].chardata_for_range = malloc(
      sizeof(stbtt_packedchar) * (char_count_in_block)
  );
  font->packing.count += 1;
}

void fc_cook(struct fc_font * font) {
  stbtt_pack_context pack_context;
  size_t block_count = font->packing.count;
  stbtt_pack_range * blocks = font->packing.blocks;
  struct fc_size dimensions = fc_calculate_pixel_buffer_size(
      blocks,
      block_count,
      font->metadata.size.value
  );
  size_t pixel_count = (size_t) (dimensions.width * dimensions.height);
  unsigned char * pixels_1bpp = malloc(pixel_count);
  unsigned char * pixels_4bpp = malloc(pixel_count * 4);

  fc_generate_metrics(font);

  stbtt_pack_range * ranges = font->packing.blocks;

  stbtt_PackBegin(
      &pack_context, pixels_1bpp,
      (int) dimensions.width, (int) dimensions.height,
      0, 1, NULL
  );
  stbtt_PackFontRanges(
      &pack_context,
      font->metadata.font_data,
      0,
      ranges,
      (int) block_count
  );

  stbtt_PackEnd(&pack_context);

  fc_colorify(
      pixels_1bpp,
      pixels_4bpp,
      dimensions,
      font->metadata.color
  );

  font->pixels.data = pixels_4bpp;
  font->pixels.dimensions = dimensions;
  free(pixels_1bpp);
}

int fc_render(
    struct fc_font const * font,
    unsigned char const * text,
    size_t byte_count,
    struct fc_character_mapping * mapping
) {
  size_t target_index = 0;
  stbtt_pack_range * block;
  float x = 0, y = 0, kern = 0/*, top_offset = 0.0f*/;
  struct utf8_decode_result decode;
  float pw = font->pixels.dimensions.width, ph = font->pixels.dimensions.height;

  /* decode all utf8 characters into unicode codepoints, find their
   * block, gets their rendering parameters, adds kerning */
  for (size_t i = 0; i < byte_count; i += decode.skip, target_index++) {
    decode = utf8_decode(text + i, byte_count - i);
    block = fc_locate_block(font, decode.codepoint);
    /* skips half the pixel "height" if block was not found */
    if (block == NULL) {
      x += font->metadata.size.value / 2;
      continue;
    }

    x += kern;

    stbtt_aligned_quad quad;
    stbtt_GetPackedQuad(
        block->chardata_for_range,
        (int) pw,
        (int) ph,
        (int) (decode.codepoint - block->first_unicode_codepoint_in_range),
        &x, &y, &quad, 1
    );

    struct fc_character_mapping * m = &mapping[target_index];
    struct fc_rect * src = &m->source, * dst = &m->target;


    src->left = quad.s0 * pw;
    src->top = quad.t0 * ph;
    src->right = quad.s1 * pw;
    src->bottom = quad.t1 * ph;

    dst->left = quad.x0;
    dst->top = quad.y0;
    dst->right = quad.x1;
    dst->bottom = quad.y1;

    m->codepoint = decode.codepoint;

    /* stores the top offset to add it later to the mappings, to make sure
     * that rendering starts at 0 */
//    if ((dst->top < top_offset) || target_index == 0)
//      top_offset = dst->top;

    /* checks to see if there is kerning to add to the next character, and
     * sets it to be used in the next iteration */
    kern = 0;
    if (i + decode.skip < byte_count) {
      struct utf8_decode_result next = utf8_decode(
          text + i + decode.skip,
          byte_count - (i + decode.skip)
      );
      kern = fc_get_kern(font, decode.codepoint, next.codepoint);
    }
  }

  /* characters are rendered around a baseline, which was set to 0 when
   * fc_cook was called. the following loop goes through all glyph
   * mappings and adjusts them to remove the "empty" space on top caused
   * by that. */
//  top_offset = fc_fabs(top_offset);
//  for (size_t i = 0; i < target_index; i++) {
//    mapping[i].target.top += top_offset;
//    mapping[i].target.bottom += top_offset;
//  }

  /* end of the loop, target_index will be the amount of decoded glyphs */
  return (int) target_index;
}

struct fc_font_size fc_get_font_size(struct fc_font const * font) {
  return font->metadata.size;
}

struct fc_color fc_get_color(struct fc_font const * font) {
  return font->metadata.color;
}

uint8_t const * fc_get_font_data(struct fc_font const * font) {
  return font->metadata.font_data;
}

size_t fc_get_block_count(struct fc_font const * font) {
  return font->packing.count;
}

struct fc_unicode_block fc_get_block_at(struct fc_font const * font, size_t index) {
  struct fc_unicode_block r = {
      .first = 0,
      .last = 0,
      .count = 0
  };
  if (index >= font->packing.count) return r;
  r.first = font->packing.blocks[index].first_unicode_codepoint_in_range;
  r.count = font->packing.blocks[index].num_chars;
  r.last = r.first + r.count;
  return r;
}


struct fc_pixels const * fc_get_pixels(struct fc_font const * font) {
  return &font->pixels;
}

void fc_destruct(struct fc_font * font) {
  free(font->pixels.data);
  free(font->metadata.info);
  for (size_t i = 0; i < font->packing.count; i++) {
    free(font->packing.blocks[i].chardata_for_range);
  }
  free(font->packing.blocks);
  free(font);
}

int fc_render_wrapped(
    struct fc_font const * font,
    unsigned char const * text,
    size_t byte_count,
    size_t line_width,
    float line_height_multiplier,
    enum fc_alignment alignment,
    struct fc_character_mapping * mapping
) {
  int rendered = fc_render(font, text, byte_count, mapping);
  struct fc_size space_metrics = fc_get_space_metrics(font);
  fc_wrap(mapping, rendered, (float) line_width, font->metrics.line_height * line_height_multiplier, space_metrics.width, alignment);
  return rendered;
}

struct fc_size fc_get_space_metrics(struct fc_font const * font) {
  int aw, lsb;
  float space_width;
  struct fc_size r;

  stbtt_GetCodepointHMetrics(font->metadata.info, 0x20, &aw, &lsb);
  space_width = (float) (aw + lsb) * font->metrics.scale;
  r.width = space_width;
  r.height = font->metrics.line_height;
  return r;
}
