#ifndef FONT_CHEF_FONT_HPP
#define FONT_CHEF_FONT_HPP

/**
 * @file font.hpp
 * This file contains a wrapper class for ::fc_font.
 */

#include "font-chef/font-chef-export.h"
#include "font-chef/font.h"
#include <cstring>

#include <string>
#include <vector>

#include "font-chef/font-size.hpp"
#include "font-chef/color.hpp"
#include "font-chef/render-result.hpp"

namespace fc {
  /**
   * @brief A wrapper class for ::fc_font.
   * @ingroup font
   * @ingroup cpp
   *
   * You can construct a fc::font yourself or you can use fc::from (which is preferred if you are going
   * to use method chaining, see fc::from for an examples).
   */
  class FONT_CHEF_EXPORT font {
    private:
      fc_font * data;

    public:
    /**
     * @brief Move constructor
     * @param other The other fc::font instance to move from.
     */
      font(font && other) noexcept : data(other.data) {
        other.data = nullptr;
      };

      /**
       * @brief Copy constructor
       * @warning It does not actually *copy* anything. It reconstructs another fc::font instance with the same steps used to construct the other.
       * @param other The other fc::font instance to copy from
       */
      font(font const & other)
      : data(fc_construct(
          fc_get_font_data(other.data),
          fc_get_font_size(other.data),
          fc_get_color(other.data))
      ) {
        size_t block_count = fc_get_block_count(other.data);
        for (size_t i = 0; i < block_count; i++) add(fc_get_block_at(other.data, i));
        if (fc_get_pixels(other.data) != nullptr) cook();
      }

      /**
       * @brief Constructs a fc::font instance from a font data, a font size and a font color
       * @param font_data The font data in memory
       * @param font_size The size of the font, either in fc::px or fc::pt
       * @param font_color The color of the font
       * @sa ::fc_construct
       */
      font(uint8_t const * font_data, fc::font_size const & font_size, fc::color const & font_color)
        : data(fc_construct(font_data, font_size.data, font_color.data)) { };

      /**
       * @brief Destructs a fc::font instance and frees all the memory associated with it
       * @sa ::fc_destruct
       */
      ~font() {
        if (data) fc_destruct(data);
      }

      /**
       * @brief Adds a new unicode block to be cooked.
       *
       * This is the `lvalue` version of this method (objects with a name)
       *
       * @param block The block to be cooked
       * @return *this
       * @sa ::fc_add
       */
      font & add(fc_unicode_block const & block) & {
        return add(block.first, block.last);
      }


      /**
       * @brief Adds a new unicode block to be cooked
       *
       * This is the `rvalue` version of this method (objects without a name)
       *
       * @param block The block to be cooked
       * @return *this
       * @sa ::fc_add
       */
      font && add(fc_unicode_block const & block) && {
        return std::move(add(block.first, block.last));
      }

      /**
       * @brief Adds a new unicode range to be cooked
       *
       * This is the `lvalue` version of this method (objects with a name)
       *
       * @param first The first unicode point in the range
       * @param last The last unicode point in the range
       * @return *this
       * @sa ::fc_add
       */
      font & add(uint32_t first, uint32_t last) & {
        fc_add(data, first, last);
        return *this;
      }


      /**
       * @brief Adds a new unicode range to be cooked
       *
       * This is the `rvalue` version of this method (objects without a name)
       *
       * @param first The first unicode point in the range
       * @param last The last unicode point in the range
       * @return *this
       * @sa ::fc_add
       */
      font && add(uint32_t first, uint32_t last) && {
        fc_add(data, first, last);
        return std::move(*this);
      }

      /**
       * @brief Cooks all the added unicode ranges into a pixmap and clipping information
       *
       * This is the `lvalue` version of this method (objects with a name)
       *
       * @return *this
       * @sa ::fc_cook
       */
      font & cook() & {
        fc_cook(data);
        return *this;
      }


      /**
       * @brief Cooks all the added unicode ranges into a pixmap and clipping information
       *
       * This is the `rvalue` version of this method (objects without a name)
       *
       * @return *this
       * @sa ::fc_cook
       */
      font && cook() && {
        fc_cook(data);
        return std::move(*this);
      }

      /**
       * @brief Obtains a structure containing a pointer to the pixel data and it's dimensions
       *
       * Use this function when you want to create a texture after cooking the font with the desired
       * unicode blocks/ranges
       *
       * @return a ::fc_pixels value
       */
      fc_pixels pixels() const {
        return *fc_get_pixels(data);
      }

      /**
       * @brief Produces clipping and target rectangles to render specified text
       *
       * This is equivalent to calling ::fc_render but a lot easier. It returns an instance of
       * fc::render_result that contains the character mapping vector.
       *
       * **Example**
       * @code
       * fc::font font; // suppose a font that has already been cooked
       * fc::render_result result = font.render("Hello world!");
       * @endcode
       *
       * @param text The text to render
       * @return An instance of fc::render_result
       * @sa ::fc_render
       * @sa ::fc::render_result
       */
      fc::render_result render(std::string const & text) const {
        fc::render_result result(data);
        return std::move(render(text, result));
      }

      /**
       * @brief Produces clipping and target rectangles to render specified text reusing an instance of fc::render_result
       *
       * You can use this function if you already have an instance of fc::render_result and
       * want to reuse it without allocating a new one. The vector will be reallocated if needed.
       *
       * @param text The text to render
       * @param result The fc::render_result instance to reuse
       * @return The same fc::render_result reference passed in @p result argument.
       * @sa ::fc_render
       * @sa ::fc::render_result
       * @sa ::fc::font::render
       */
      fc::render_result & render(std::string const & text, fc::render_result & result) const {
        result.font = data;
        std::vector<fc_character_mapping> & mapping = result.mapping;
        if (mapping.size() < text.length()) mapping.resize(text.length());
        struct fc_render_result r = fc_render(data, (uint8_t *) text.data(), text.size(), mapping.data());
        mapping.resize(r.glyph_count);
        result.line_count = r.line_count;
        return result;
      }
  };

  /**
   * @brief A helper method to ease font cooking via method chaining
   * @ingroup cpp
   *
   * **Example**
   * @code
   * auto font = fc::from(fdata, fc::px(12), fc::rgb(255, 0, 0))
   *                .add(fc_unicode_block_basic_latin)
   *                .add(fc_unicode_block_latin_1_supplement)
   *                .cook()
   * @endcode
   *
   * @param font_data The font data to pass to fc::font constructor
   * @param font_size The font size to pass to fc::font constructor
   * @param font_color The font color to pass to fc::font constructor
   * @return A fc::font instance
   * @sa fc::font::font
   * @sa ::fc_construct
   */
  FONT_CHEF_EXPORT font from(uint8_t const * font_data, fc::font_size const & font_size, fc::color const & font_color) {
    font r(font_data, font_size, font_color);
    return r;
  }
}

#endif //FONT_CHEF_FONT_HPP
