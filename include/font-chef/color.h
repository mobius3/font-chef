#ifndef FONT_CHEF_COLOR_H
#define FONT_CHEF_COLOR_H

/**
 * @file color.h
 * This file contains the fc_color structure and functions to work with it.
 */

/**
 * @defgroup color Color
 * All the functions and types that deal with font colors
 */

#include "font-chef/font-chef-export.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Represents a 4-byte-per-pixel color with red, green, blue and alpha components.
 * @ingroup color
 */
struct fc_color {
  /** The red component (0 to 255) */
  uint8_t r;

  /** The green component (0 to 255) */
  uint8_t g;

  /** The blue component (0 to 255) */
  uint8_t b;

  /** The alpha component (0 to 255). 0 means transparent, 255 means fully opaque */
  uint8_t a;
};

/**
 * @brief Zeroes all fields of a `fc_color` structure.
 * @ingroup color
 *
 * Note that simply using `struct fc_color color = {}` is equivalent and faster.
 *
 * **Example**
 * @code
 * struct fc_color color;
 * fc_color_construct(&color);
 * @endcode
 *
 * @param color A pointer to a `fc_color` value
 */
FONT_CHEF_EXPORT extern void fc_color_construct(struct fc_color * color);

/**
 * @brief Sets all fields of a `fc_color` structure at once.
 * @ingroup color
 *
 * **Example**
 * @code
 * struct fc_color my_red = fc_color_red;
 * fc_color_set(&my_red, 255, 100, 100, 255);
 * @endcode
 *
 * @param color A pointer to a `fc_color` value to be set
 * @param r The red component to be set
 * @param g The green component to be set
 * @param b The blue component to be set
 * @param a The alpha component to be set
 */
FONT_CHEF_EXPORT extern void fc_color_set(struct fc_color * color, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

/**
 * @brief Constructs and return a `fc_color` value with the provided components set
 * @ingroup color
 *
 * **Example**
 * @code
 * struct fc_color translucent_red = fc_rgba(255, 0, 0, 128);
 * @endcode
 *
 * @param r The red component
 * @param g The green component
 * @param b The blue component
 * @param a The alpha component
 * @return A `fc_color` value with the components set
 */
FONT_CHEF_EXPORT extern struct fc_color fc_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

/**
 * @brief Constructs and return a `fc_color` value with the provided components set and alpha set as 255 (opaque)
 * @ingroup color
 *
 * **Example**
 * @code
 * struct fc_color red = fc_rgb(255, 0, 0);
 * @endcode
 *
 * @param r The red component
 * @param g The green component
 * @param b The blue component
 * @return A `fc_color` value with the components set and alpha set to 255
 */
FONT_CHEF_EXPORT extern struct fc_color fc_rgb(uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief Constructs and return a `fc_color` value with red, green and blue components
 * extracted from an unsigned 32-bit integer, sets alpha to 255
 * @ingroup color
 *
 * **Example**
 * @code
 * struct fc_color red = fc_0xrgb(0xFF0000);
 * @endcode
 *
 * @param color The color encoded as 32-bit unsigned integer to use
 * @return A `fc_color` value with the components extracted from the integer and alpha set to 255
 */
FONT_CHEF_EXPORT extern struct fc_color fc_0xrgb(uint32_t color);


/**
 * @brief Constructs and return a `fc_color` value with red, green and blue components
 * extracted from an unsigned 32-bit integer
 * @ingroup color
 *
 * **Example**
 * @code
 * struct fc_color red = fc_0xrgba(0xFF000080);
 * @endcode
 *
 * @param color The color encoded as 32-bit unsigned integer to use
 * @return A `fc_color` value with the components extracted from the integer
 */
FONT_CHEF_EXPORT extern struct fc_color fc_0xrgba(uint32_t color);

/**
 * @brief RGBA: `#FF0000FF`
 * @ingroup color
 */
FONT_CHEF_EXPORT extern struct fc_color const fc_color_red;

/**
 * @brief RGBA: `#00FF00FF`
 * @ingroup color
 */
FONT_CHEF_EXPORT extern struct fc_color const fc_color_green;

/**
 * @brief RGBA: `#0000FFFF`
 * @ingroup color
 */
FONT_CHEF_EXPORT extern struct fc_color const fc_color_blue;

/**
 * @brief RGBA: `#FFFFFFFF`
 * @ingroup color
 */
FONT_CHEF_EXPORT extern struct fc_color const fc_color_white;

/**
 * @brief RGBA: `#000000FF`
 * @ingroup color
 */
FONT_CHEF_EXPORT extern struct fc_color const fc_color_black;

#ifdef __cplusplus
}
#endif

#endif /* FONT_CHEF_COLOR_H */
