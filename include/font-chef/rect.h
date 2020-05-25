#ifndef FONT_CHEF_RECT_H
#define FONT_CHEF_RECT_H

/**
 * @file rect.h
 * This file provides the struct `fc_rect` that represents a rectanle with left, top, right and bottom values.
 */

/**
 * @defgroup rect Rectangle
 * Functions and types that deal with rectangles
 */

#include "font-chef/font-chef-export.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Represents a rectangle with `left`, `top`, `right` and `bottom` float values.
 * @ingroup rect
 *
 * Although `left` and `top` can be used as `x` and `y`,
 * `bottom` and `right` *are not the same* as width and height. They are absolute values
 * from origin (0, 0).
 *
 * **Example**
 * @code
 * struct fc_rect r = { 0, 0, 100, 100 };
 * @endcode
 */
struct fc_rect {
  /** @brief Left value */
  float left;

  /** @brief Top value */
  float top;

  /** @brief Right value */
  float right;

  /** @brief Bottom value */
  float bottom;
};

/**
 * @brief Calculates and returns the width of a rect represented by a `fc_rect` value.
 * @ingroup rect
 *
 * This is equivalent to `(rect->right - rect->left)`
 *
 * **Example**
 * @code
 * struct fc_rect rect = { 100, 0, 500, 100 };
 * float width = fc_rect_width(&rect); // returns 400
 * @endcode
 *
 * @param rect A pointer to a `fc_rect` value to calculate width
 * @return The calculated width
 * @sa fc_rect_height
 */
FONT_CHEF_EXPORT extern float fc_rect_width(struct fc_rect const * rect);

/**
 * @brief Calculates and returns the height of a rect represented by a `fc_rect` value.
 * @ingroup rect
 *
 * This is equivalent to `(rect->bottom - rect->top)`
 *
 * **Example**
 * @code
 * struct fc_rect rect = { 100, 0, 500, 100 };
 * float width = fc_rect_height(&rect); // returns 100
 * @endcode
 *
 * @param rect A pointer to a `fc_rect` value to calculate height
 * @return The calculated height
 * @sa fc_rect_width
 */
FONT_CHEF_EXPORT extern float fc_rect_height(struct fc_rect const * rect);

#ifdef __cplusplus
}
#endif

#endif /* FONT_CHEF_RECT_H */
