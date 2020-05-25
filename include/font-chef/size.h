#ifndef FONT_CHEF_SIZE_H
#define FONT_CHEF_SIZE_H

/**
 * @file size.h
 * This file provides the `fc_size` structure, with width and height fields
 */

/**
 * @defgroup size Size
 * The fc_size structure
 */

#include "font-chef/font-chef-export.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Contains width and height as floats.
 * @ingroup size
 */
struct fc_size {
  /** @brief The width value */
  float width;

  /** @brief The height value */
  float height;
};

#ifdef __cplusplus
}
#endif

#endif /* FONT_CHEF_SIZE_H */
