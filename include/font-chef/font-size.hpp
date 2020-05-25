#ifndef FONT_CHEF_FONT_SIZE_HPP
#define FONT_CHEF_FONT_SIZE_HPP

/**
 * @file font-size.hpp
 * This file contains a wrapper class for the structure ::fc_font_size
 */

#include "font-chef/font-chef-export.h"
#include "font-chef/font-size.h"

namespace fc {
  /**
   * @brief A wrapper class for ::fc_font_size
   * @ingroup cpp
   * @ingroup font-size
   */
  struct FONT_CHEF_EXPORT font_size {
    /**
     * @brief the actual ::fc_font_size data. You can and are encouraged to use it directly, if needed.
     */
      fc_font_size data;

      /** Empty font_size constructor */
      font_size() : data() {};

      /**
       * @brief Creates a fc::font_size instance from a fc_font_size structure, copying its contents.
       *
       * This constructor exists mainly to provide implicit automatic conversion from ::fc_font_size to fc::font_size
       *
       * @param fs the fc_font_size value to copy from
       * @sa ::fc_px
       * @sa ::fc_pt
       */
      font_size(fc_font_size const & fs) : data(fs) {} //NOLINT

    /**
     * @brief Default copy-constructor for fc::font_size
     * @param other The fc::font_size instance to copy from
     */
      font_size(font_size const & other) = default;

      /**
       * @brief Constructs a font size from a value and a type
       * @param value The value for the font-size
       * @param type The type (pt or px) for this instance
       */
      font_size(float value, enum fc_font_size_type type) : data{value, type} {}
  };

  /**
   * @brief Constructs a fc::font_size instance in pixels with specified value
   * @ingroup cpp
   * @param v The value size, in pixels, for this font
   * @return A fc::font_size instance
   * @sa ::fc_px
   */
  FONT_CHEF_EXPORT inline font_size px(float v) {
    return font_size(v, fc_size_type__px);
  }

  /**
   * @brief Constructs a fc::font_size instance in points with specified value
   * @ingroup cpp
   * @param v The value size, in points, for this font
   * @return A fc::font_size instance
   * @sa ::fc_pt
   */
  FONT_CHEF_EXPORT inline font_size pt(float v) {
    return font_size(v, fc_size_type__pt);
  }
}

#endif //FONT_CHEF_FONT_SIZE_HPP
