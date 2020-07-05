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
  }

  return r;
}

struct fc_text_segment {
  size_t begin;
  size_t end;
};

float fc_text_segment_width(struct fc_text_segment const * segment, struct fc_character_mapping const * mapping) {
  return mapping[segment->end].target.right - mapping[segment->begin].target.left;
}

void fc_wrap(struct fc_character_mapping mapping[], size_t glyph_count, float line_width, float line_height, float space_width, enum fc_alignment aligment) {
  struct fc_text_segment * words = calloc(sizeof(*words), glyph_count);
  struct fc_text_segment * lines = calloc(sizeof(*lines), glyph_count);
  size_t word_count = 0;

  /* identify all the words. this is ugly and I'm a noob. */
  size_t i = 0;
  for (i = 0; i < glyph_count; i++) {
    struct fc_character_mapping * m = &mapping[i];
    if (m->codepoint == 0x20 || (i + 1 >= glyph_count)) {
      words[word_count].end = i + (i + 1 >= glyph_count ? 0 : -1);
      word_count++;

      /* no more glyphs, hence no more words */
      if (i + 1 >= glyph_count) break;

      /* skip spaces */
      while (m->codepoint == 0x20 && i + 1 < glyph_count) {
        ++i;
        m = &mapping[i];
      }

      /* all that was left was spaces. no more words */
      if (i + 1 >= glyph_count) break;

      /* start a new word */
      words[word_count].begin = i;
    }
  }

  /* identify lines */
  float space_left = line_width;
  size_t line_count = 1;
  for (size_t word_index = 0; word_index < word_count; word_index++) {
    struct fc_text_segment * word = &words[word_index];
    struct fc_rect bounds = fc_text_bounds(mapping + word->begin, word->end - word->begin +1);
    float word_width = fc_rect_width(&bounds);
    if (((word_width + space_width) > space_left) && word_index > 0) {
      line_count++;
      lines[line_count-1].begin = words[word_index].begin;
      space_left = line_width - word_width;
    } else {
      space_left -= word_width + space_width;
    }
    lines[line_count-1].end = words[word_index].end;
  }

  /* ajust yadd and xadd for lines according to alignment */
  float xadd, yadd;
  for (size_t line_i = 0; line_i < line_count; line_i++) {
    yadd = line_i * line_height;
    xadd = -mapping[lines[line_i].begin].target.left;
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
    for (size_t glyph_i = lines[line_i].begin; glyph_i <= lines[line_i].end; glyph_i++) {
      struct fc_rect * dst = &mapping[glyph_i].target;
      dst->left += xadd;
      dst->right += xadd;
      dst->top += yadd;
      dst->bottom += yadd;
    }
  }
  free(words);
  free(lines);
}

void fc_move(struct fc_character_mapping * mapping, size_t count, float left, float baseline) {
  for (size_t i = 0; i < count; i++) {
    mapping[i].target.top += baseline;
    mapping[i].target.bottom += baseline;
    mapping[i].target.left += left;
    mapping[i].target.right += left;
  }
}
