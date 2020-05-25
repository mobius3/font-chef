#include "font-chef/color.h"

#define gmt_u8(n) (((unsigned char) n))

struct fc_color const fc_color_red = {255, 0, 0, 255};
struct fc_color const fc_color_green = {0, 255, 0, 255};
struct fc_color const fc_color_blue = {0, 0, 255, 255};
struct fc_color const fc_color_white = {255, 255, 255, 255};
struct fc_color const fc_color_black = {0, 0, 0, 255};

struct fc_color fc_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  struct fc_color result = {r, g, b, a};
  return result;
}

struct fc_color fc_rgb(uint8_t r, uint8_t g, uint8_t b) {
  struct fc_color result = {r, g, b, 255};
  return result;
}


struct fc_color fc_0xrgba(uint32_t hex) {
  struct fc_color color = {
    .r = gmt_u8((hex >> 24u) & 0xffu),
    .g = gmt_u8((hex >> 16u) & 0xffu),
    .b = gmt_u8((hex >> 8u) & 0xffu),
    .a = gmt_u8((hex & 0xffu))
  };
  return color;
}

struct fc_color fc_0xrgb(uint32_t hex) {
  struct fc_color color = {
    .r = gmt_u8((hex >> 16u) & 0xffu),
    .g = gmt_u8((hex >> 8u) & 0xffu),
    .b = gmt_u8(hex & 0xffu),
    .a = 255
  };
  return color;
}

void fc_color_construct(struct fc_color * color) {
  color->r = color->g = color->b;
  color->a = 255;
}

void fc_color_set(
  struct fc_color * color,
  uint8_t r,
  uint8_t g,
  uint8_t b,
  uint8_t a
) {
  color->r = r;
  color->g = g;
  color->b = b;
  color->a = a;
}

