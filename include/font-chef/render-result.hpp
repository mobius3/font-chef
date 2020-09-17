#ifndef FONT_CHEF_RENDER_RESULT_HPP
#define FONT_CHEF_RENDER_RESULT_HPP

#include "font-chef/character-mapping.h"
#include "font-chef/font.h"
#include <vector>
#include <cstdio>


/**
 * @file render-result.hpp
 * Has the fc::render_result structure
 */

namespace fc {

  /**
   * @brief Wraps a `std::vector<fc_character_mapping>`.
   * @ingroup character-mapping
   *
   * It's mainly a quality of life improvement over working with a vector directly. It supports move semantics
   * to allow for method chaining and it also supports iterators and range-based for loops.
   *
   * **Example**
   * @code
   * fc::font font; // suppose a font that has already been cooked
   * fc::render_result result = font.render("Hello world!").wrap(100.0f).move(0.0f, 50.0f);
   * @endcode
   */
  struct FONT_CHEF_EXPORT render_result {
    /**
     * @brief A vector of character mappings produced after calling fc::font::render
     */
    std::vector<::fc_character_mapping> mapping;

    /**
     * @brief How many lines were produced
     */
     uint32_t line_count;

    /**
     * @brief A pointer to the ::fc_font used to generate this mapping
     */
    fc_font * font;

    /**
     * @brief Constructs a fc::render_result instance with a font and with a mapping vector
     *
     * This constructor exists mainly to be used by fc::font::render. You probably will never use it
     * directly.
     *
     * @param font The font used to generate the contained mapping
     * @param mapping A movable reference to a vector of character mappings
     * @sa fc::font::render
     */
    render_result(fc_font * font = nullptr, std::vector<fc_character_mapping> && mapping = {}) //NOLINT
        : mapping(mapping), font(font), line_count(0) {
      ::printf("construct render result");
    };

    /**
     * @brief Move constructor of fc::render_result.
     * @param other A rvalue (moveable) ref to a fc::render_result instance
     */
    render_result(render_result && other) noexcept
      : mapping(std::move(other.mapping)), font(other.font), line_count(other.line_count) {
      other.font = nullptr;
    };

    /**
     * @brief Move assignment operator for fc::render_result
     * @param other A rvalue (moveable) ref to a fc::render_result instance
     * @return *this
     */
    render_result & operator=(render_result && other) noexcept {
      if (this == &other) return *this;
      this->mapping = std::move(other.mapping);
      this->font = other.font;
      this->line_count = other.line_count;
      other.font = nullptr;
      return *this;
    }

    /**
     * @brief Copy assignment operator for fc::render_result
     * @param other A const lvalue (non-moveable) ref to a fc::render_result instance
     * @return *this
     */
    render_result & operator=(render_result const & other) noexcept {
      this->font = other.font;
      if (this == &other) return *this;
      return *this;
    }

    /**
     * @brief Calls ::fc_wrap on the vector of character mappings
     *
     * The arguments are similar to ::fc_render_wrapped but calling this is much simpler. It produces the same result.
     * Calling fc::render_result::wrap multiple times produces weird results. Call it only once after fc::font::render.
     *
     * This is the lvalue version of this function.
     *
     *
     * **Example**
     * @code
     * fc::font font; // suppose a font that has already been cooked
     * auto result = font.render("Hello world!");
     * result.wrap(80.0f);
     * @endcode
     *
     * @param line_width The maximum line width, in target/screen size (e.g, pixels)
     * @param line_height_multiplier A value that can be used to increase the line height/spacing
     * @param alignment Which aligment should lines follow
     * @return *this
     */
    render_result &
    wrap(float line_width, float line_height_multiplier = 1.0f, fc_alignment alignment = fc_align_left) & {
      if (!font) return *this;
      fc_size space_metrics = fc_get_space_metrics(font);
      this->line_count = fc_wrap(
          mapping.data(),
          mapping.size(),
          line_width,
          space_metrics.height,
          space_metrics.width * line_height_multiplier,
          alignment
      );
      return *this;
    }

    /**
     * @brief Calls ::fc_wrap on the vector of character mappings
     *
     * The arguments are similar to ::fc_render_wrapped but calling this is much simpler. It produces the same result.
     * Calling fc::render_result::wrap multiple times produces weird results. Call it only once after fc::font::render.
     *
     * This is the rvalue version of this function and returns a moveable *this. It is here mainly to assist
     * in method chaining.
     *
     * **Example**
     * @code
     * fc::font font; // suppose a font that has already been cooked
     * auto result = font.render("Hello world!").wrap(80.0f);
     * @endcode
     *
     * @param line_width The maximum line width, in target/screen size (e.g, pixels)
     * @param line_height_multiplier A value that can be used to increase the line height/spacing
     * @param alignment Which aligment should lines follow
     * @return *this
     */
    render_result &&
    wrap(float line_width, float line_height_multiplier = 1.0f, fc_alignment alignment = fc_align_left) && {
      return std::move(wrap(line_width, line_height_multiplier, alignment));
    }


    /**
     * @brief This is a wrapper to ::fc_move. Consult its documentation for more information.
     *
     * This is the lvalue (non-moveable) version of this function
     *
     * **Example**
     * @code
     * fc::font font; // suppose a font that has already been cooked
     * auto result = font.render("Hello world!").move(0.0f, 50.0f);
     * @endcode
     *
     * @param left Left position where the text should start rendering
     * @param baseline Amount to add to the text baseline
     */
    render_result & move(float left = 0.0f, float baseline = 0.0f) & {
      fc_move(mapping.data(), mapping.size(), left, baseline);
      return *this;
    }

    /**
     * @brief This is a wrapper to ::fc_move. Consult its documentation for more information.
     *
     * This is the rvalue (moveable) version of this function mainly to be used with method chaining.
     *
     * **Example**
     * @code
     * fc::font font; // suppose a font that has already been cooked
     * auto result = font.render("Hello world!").move(0.0f, 50.0f);
     * @endcode
     *
     * @param left Left position where the text should start rendering
     * @param baseline Amount to add to the text baseline
     */
    render_result && move(float left = 0.0f, float baseline = 0.0f) && {
      return std::move(move(left, baseline));
    }

    /**
     * @brief Returns an iterator pointing to the first character mapping
     * @return mapping.begin();
     */
    std::vector<::fc_character_mapping>::iterator begin() {
      return mapping.begin();
    }

    /**
     * @brief Returns an iterator pointing to the end+1 character mapping
     * @return mapping.end();
     */
    std::vector<::fc_character_mapping>::iterator end() {
      return mapping.end();
    }

    /**
     * @brief Returns the size of the mapping vector (i.e, the number of mappings)
     * @return mapping.size();
     */
    size_t size() const {
      return mapping.size();
    }
  };
}

#endif
