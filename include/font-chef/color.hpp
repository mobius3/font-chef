#ifndef FONT_CHEF_COLOR_HPP
#define FONT_CHEF_COLOR_HPP

/**
 * @file color.hpp
 * This file contains a wrapper class for ::fc_color.
 */

#include "font-chef/font-chef-export.h"
#include "font-chef/color.h"

namespace fc {
  /**
   * @brief A wrapper class for ::fc_color.
   * @ingroup cpp
   * @ingroup color
   */
  struct FONT_CHEF_EXPORT color {
    /**
     * @brief The internal ::fc_color value
     */
    fc_color data;

    /** Constructs a black, fully transparent color */
    color() : data() { }

    /** @brief Creates a fc::color instance from a ::fc_color value
     *
     * This constructor exists mainly to provide implicit automatic conversion from ::fc_font_size to fc::font_size
     *
     * @param c The ::fc_color value to construct from
     * */
    color(fc_color const & c) : data(c) { } //NOLINT

    /**
     * @brief Default copy-constructor for fc::color
     * @param other The fc::color instance to copy from
     */
    color(color const & other) = default;

    /**
     * @brief Constructs a fc::color instance from red, green, blue and alpha components
     * @param r The red component
     * @param g The green component
     * @param b The blue component
     * @param a The alpha component (default: 255, fully opaque)
     * @sa ::fc_color_set
     */
    color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) : data{r, g, b, a} { }

    /**
     * @brief Gets the red component for this color
     * @return The red component for this color
     */
    uint8_t r() const { return data.r; }

    /**
     * @brief Gets the green component for this color
     * @return The green component for this color
     */
    uint8_t g() const { return data.g; }

    /**
     * @brief Gets the blue component for this color
     * @return The blue component for this color
     */
    uint8_t b() const { return data.b; }

    /**
     * @brief Gets the alpha component for this color
     * @return The alpha component for this color
     */
    uint8_t a() const { return data.a; }

    /**
     * @brief Sets the red component for this color
     * @return *this
     */
    color & r(uint8_t v) { data.r = v; return *this; }

    /**
     * @brief Sets the green component for this color
     * @return *this
     */
    color & g(uint8_t v) { data.g = v; return *this; }

    /**
     * @brief Sets the blue component for this color
     * @return *this
     */
    color & b(uint8_t v) { data.b = v; return *this; }

    /**
     * @brief Sets the alpha component for this color
     * @return *this
     */
    color & a(uint8_t v) { data.a = v; return *this; }
  };

  /**
   * @brief Constructs a fc::color instance from an integer with red, green, blue and alpha components
   * @ingroup cpp
   * @param c An integer in the form `0xRRGGBBAA`
   * @return A fc::color instance
   * @sa ::fc_0xrgba
   */
  FONT_CHEF_EXPORT inline color rgba(uint32_t c) {
    fc_color r = fc_0xrgba(c);
    return color(r);
  }

  /**
   * @brief Constructs a fc::color instance from red, green, blue and alpha values
   * @ingroup cpp
   * @param r The red component
   * @param g The green component
   * @param b The blue component
   * @param a The alpha component
   * @return A fc::color instance
   * @sa ::fc_rgba
   */
  FONT_CHEF_EXPORT inline color rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    return color(r, g, b, a);
  }

  /**
   * @brief Constructs a fc::color instance from red, green and blue values, alpha will be set to 255 (opaque)
   * @ingroup cpp
   * @param r The red component
   * @param g The green component
   * @param b The blue component
   * @return A fc::color instance
   * @sa ::fc_rgb
   */
  FONT_CHEF_EXPORT inline color rgb(uint8_t r, uint8_t g, uint8_t b) {
    return color(r, g, b);
  }

  /**
   * @brief Constructs a fc::color instance from an integer with red, green and blue components, alpha will be set to 255 (opaque)
   * @ingroup cpp
   * @param c An integer in the form `0x__RRGGBB` (leftmost byte is ignored)
   * @return A fc::color instance
   * @sa ::fc_0xrgb
   */
  FONT_CHEF_EXPORT inline color rgb(uint32_t c) {
    fc_color r = fc_0xrgb(c);
    return color(r);
  }
}

#endif //FONT_CHEF_COLOR_HPP
