#include "font-chef/character-mapping.h"
#include "stb_truetype.h"
#include <stdlib.h>

struct fc_rect fc_text_bounds(struct fc_character_mapping const mapping[], size_t length) {
  struct fc_rect r = { .left = 0, .top = 0, .right = 0, .bottom = 0 };
  if (length < 1) return r;
  r.left = mapping[0].target.left;
  r.top = mapping[0].target.top;
  r.bottom = mapping[0].target.bottom;
  r.right = mapping[length -1].target.right;
  for (size_t i = 0; i < length; i++) {
    struct fc_rect const * dst = &mapping[i].target;
    if (dst->top < r.top) r.top = dst->top;
    if (dst->bottom > r.bottom) r.bottom = dst->bottom;
    if (dst->left < r.left) r.left = dst->left;
    if (dst->right > r.right) r.right = dst->right;
  }

  return r;
}

struct fc_text_segment {
  size_t first;
  size_t last;
};

float fc_text_segment_width(struct fc_text_segment const * segment, struct fc_character_mapping const * mapping) {
  return mapping[segment->last].target.right - mapping[segment->first].target.left;
}

uint32_t fc_wrap(struct fc_character_mapping mapping[], size_t glyph_count, float line_width, float line_height, float space_width, enum fc_alignment aligment) {
  struct fc_text_segment * words = calloc(sizeof(*words), glyph_count);
  struct fc_text_segment * lines = calloc(sizeof(*lines), glyph_count);
  size_t word_count = 0;

  for (size_t i = 0; i < glyph_count; i++) {
    struct fc_character_mapping * current_glyph = &mapping[i];
    struct fc_text_segment * current_word = &words[word_count];

    /* if this current word has no begin, it means it is starting at this glyph
     * and word_count got incremented below */
    if (current_word->first == 0 && word_count > 0) {
      current_word->first = i;
    }

    /* if we found a space, the word ends here and we skip to next iteration */
    if (current_glyph->codepoint == 0x20 || current_glyph->codepoint == '\0') {
      /* some fonts don't properly set target width of spaces */
      if (fc_rect_width(&current_glyph->target) < 0.01f) {
        current_glyph->target.right = current_glyph->target.left + space_width;
      }
      current_word->last = i -1;
      word_count += 1;

      /* since our words already have target rectangles, we need to move them
       * right by the space_width amount for every extra space,
       * because the line positioning algorithm below expects words to
       * be apart by a single space */
      while (mapping[i+1].codepoint == 0x20) {
        i++;
        fc_move(mapping + current_word->first, current_word->last - current_word->first +1, space_width, 0);
      }
    }

    if (i + 1 == glyph_count) {
      current_word->last = i;
      word_count += 1;
    }
  }

  /* identify lines */
  float space_left = line_width;
  size_t line_count = 1;
  for (size_t word_index = 0; word_index < word_count; word_index++) {
    struct fc_text_segment * word = &words[word_index];
    struct fc_rect bounds = fc_text_bounds(mapping + word->first, word->last - word->first + 1);
    float word_width = fc_rect_width(&bounds);
    if (((word_width + space_width) > space_left) && word_index > 0) {
      line_count++;
      lines[line_count-1].first = words[word_index].first;
      space_left = line_width - word_width;
    } else {
      space_left -= word_width + space_width;
    }
    lines[line_count-1].last = words[word_index].last;
  }

  /* ajust yadd and xadd for lines according to alignment */
  float xadd, yadd;
  for (size_t line_i = 0; line_i < line_count; line_i++) {
    yadd = line_i * line_height;
    xadd = -mapping[lines[line_i].first].target.left;
    switch (aligment) {
      default:
      case fc_align_left:
        break;
      case fc_align_center:
        xadd += (line_width - fc_text_segment_width(&lines[line_i], mapping)) / 2;
        break;
      case fc_align_right:
        xadd += line_width - fc_text_segment_width(&lines[line_i], mapping);
        break;
    }
    for (size_t glyph_i = lines[line_i].first; glyph_i <= lines[line_i].last; glyph_i++) {
      struct fc_rect * dst = &mapping[glyph_i].target;
      dst->left += xadd;
      dst->right += xadd;
      dst->top += yadd;
      dst->bottom += yadd;
    }
  }

  /* make a pass on all spaces and make sure their left and top are within printable character bounds
   * so that fc_text_bounds doesn't go all crazy */
  size_t first_non_space_index = 0;
  while (first_non_space_index < glyph_count && mapping[first_non_space_index].codepoint == 0x20) first_non_space_index++;

  for (size_t glyph_i = 0; glyph_i < glyph_count; glyph_i++) {
    if (mapping[glyph_i].codepoint != 0x20) continue;
    mapping[glyph_i].target = mapping[first_non_space_index].target;
  }
  free(words);
  free(lines);
  return line_count;
}

void fc_move(struct fc_character_mapping * mapping, size_t count, float left, float baseline) {
  for (size_t i = 0; i < count; i++) {
    mapping[i].target.top += baseline;
    mapping[i].target.bottom += baseline;
    mapping[i].target.left += left;
    mapping[i].target.right += left;
  }
}
