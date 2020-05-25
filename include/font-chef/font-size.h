#ifndef FONT_CHEF_FONT_SIZE_H
#define FONT_CHEF_FONT_SIZE_H

/**
 * @file font-size.h
 * This file provides the fc_font_size structure that aids in defining a font size in pixels (px) or points (pt)
 */

/**
 * @defgroup font-size Font size
 * Functions and types that deal with font sizes
 */

#include "font-chef/font-chef-export.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Used to tell if a `fc_font_size` value is specified in pixels or in points
 * @ingroup font-size
 */
enum fc_font_size_type {
  fc_size_type__pt,
  fc_size_type__px
};

/**
 * @brief Specifies the size of a font either in pixels or in points
 * @ingroup font-size
 */
struct fc_font_size {
  /**
   * @brief The value of this font size
   */
  float value;

  /**
   * @brief Specifies if the font size is in pixels or points
   */
  enum fc_font_size_type type;
};

/**
 * @brief Constructs and returns a `fc_size` value specified as points
 * @ingroup font-size
 * @param value The size in floats
 * @return A `fc_size` value using `fc_size_type__pt`
 */
FONT_CHEF_EXPORT extern struct fc_font_size fc_pt(float value);

/**
 * @brief Constructs and returns a `fc_size` value specified as pixels
 * @ingroup font-size
 * @param value The size in floats
 * @return A `fc_size` value using `fc_size_type__px`
 */
FONT_CHEF_EXPORT extern struct fc_font_size fc_px(float value);

#ifdef __cplusplus
}
#endif

#endif /* FONT_CHEF_FONT_SIZE_H */
