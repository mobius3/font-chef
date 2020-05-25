#ifndef FC_FONT_INTERNAL_H
#define FC_FONT_INTERNAL_H

#include "font-chef/size.h"
#include "font-chef/color.h"
#include "font-chef/font-size.h"
#include "font-chef/font.h"

#include <stdint.h>
#include <stddef.h>

#include "stb_truetype.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Global font metadata, including font info exctracted by stb_truetype */
struct fc_metadata {
  unsigned char const * font_data;
  struct fc_font_size size;
  struct fc_color color;
  void *info;
};

/* General metrics (ascent, descent, scale, etc) */
struct fc_metrics {
  float scale;
  float ascent;
  float descent;
  float line_gap;
  float line_height;
};

/* Before cooking, this structure holds all the blocks to be cooked. After cooking it also
 * holds the rects of everything that was cooked */
struct fc_packing {
  stbtt_pack_range * blocks;
  size_t count;
  size_t capacity;
};

/* main fc_font structure */
struct fc_font {
  struct fc_metadata metadata;
  struct fc_metrics metrics;
  struct fc_packing packing;
  struct fc_pixels pixels;
};

/* Creates a 4bpp bitmap from a 1bpp bitmap */
void fc_colorify(
    unsigned char * old_pixels,
    unsigned char * new_pixels,
    struct fc_size dimensions,
    struct fc_color color
);

float fc_get_scale(struct fc_font const * font);
float fc_get_kern(struct fc_font const * font, uint32_t ch1, uint32_t ch2);
stbtt_pack_range * fc_locate_block(struct fc_font const * font, uint32_t point);
struct fc_size fc_calculate_pixel_buffer_size(stbtt_pack_range * blocks, size_t block_count, float font_height);
void fc_generate_metrics(struct fc_font * font);

#ifdef __cplusplus
};
#endif

#endif
