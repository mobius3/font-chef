#ifndef FONT_CHEF_CHARACTER_MAPPING_H
#define FONT_CHEF_CHARACTER_MAPPING_H

#include "font-chef/size.h"
#include "font-chef/rect.h"

/**
 * @file character-mapping.h
 * This file contains the fc_character_mapping structure that aids in the text rendering process, after a font
 * was cooked. See examples in font.h file.
 */

/**
 * @defgroup character-mapping Character Mapping
 * Functions and types related to renderings result (after calling ::fc_render)
 */

#include "font-chef/font-chef-export.h"
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Specifies source and target rectangles to render the specified codepoint
 * @ingroup character-mapping
 *
 * Mapping is done in terms of source texture and target destination (screen or world-space). This structure is written by `fc_render`
 *
 * @sa ::fc_render
 */
struct fc_character_mapping {
  /**
   * @brief The source rectangle that should be used to clip the texture/surface
   */
  struct fc_rect source;
  /**
   * @brief The target rectangle, or where in the target coordinates you should render the clipped texture
   */
  struct fc_rect target;

  /**
   * @brief Which unicode codepoint this mapping represents
   */
  uint32_t codepoint;
};

/**
 * @brief Specifies an aligment to be used when rendering wrapped text
 * @ingroup character-mapping
 * @sa ::fc_wrap
 * @sa ::fc_render_wrapped
 * @sa fc::render_result::wrap
 */
enum fc_alignment {
  fc_align_left = 0,
  fc_align_center,
  fc_align_right
};

/**
 * @brief Calculates a bounding box for the rendered text
 * @ingroup character-mapping
 * @param mapping The rendering mapping (result of ::fc_render)
 * @param length How many characters were mapped
 * @return A `fc_rect` value with left, top, right and bottom values enclosing the text area
 */
FONT_CHEF_EXPORT struct fc_rect fc_text_bounds(struct fc_character_mapping const mapping[], size_t length);

/**
 * @brief Word-wraps characters in an array of ::fc_character_mapping
 * @ingroup character-mapping
 *
 * This functions identifies words and then uses a greedy algorithm to wrap lines. Keep in mind that calling
 * ::fc_wrap on an already wrapped array will produce weird results. @p line_height and @p space_width can be obtained by calling
 * ::fc_get_space_metrics, which returns both how tall and how wide a space is. You can multiply @p line_height to increase
 * between each line.
 *
 * @param mapping The array of character mappings to wrap
 * @param count How many mappings are in the array
 * @param line_width The maximum line width, in target/screen size (e.g, pixels)
 * @param line_height The space between the topmost pixel in the line to the bottomost pixel in the line (this includes characters in the line itself)
 * @param space_width The width of a space character
 * @param alignment Which aligment should lines follow
 * @return The line count in the text
 * @sa ::fc_render_wrapped
 * @sa fc::render_result::wrap
 * @sa fc_get_space_metrics
 */
FONT_CHEF_EXPORT extern uint32_t fc_wrap(
    struct fc_character_mapping mapping[],
    size_t count,
    float line_width,
    float line_height,
    float space_width,
    enum fc_alignment alignment
);

/**
 * @brief Moves all the target rectangles by @p left pixels horizontally and @p baseline pixels vertically
 * @ingroup character-mapping
 *
 * You should use this to position the text where it should start rendering in your screen.
 *
 * @warning Text rendered by ::fc_render has a baseline set at `0` (see ::fc_render for a discussion about that), so most
 * target rectangles will start rendering at negative `y` positions. Moving them by @p baseline pixels means you're moving
 * its baseline and consequentially the `y` position. But you should think in terms of baseline.
 *
 * @param mapping The array of character mappings to move
 * @param count How many mappings are in the array
 * @param left Left position where the text should start rendering
 * @param baseline Amount to add to the text baseline
 */
FONT_CHEF_EXPORT void fc_move(struct fc_character_mapping * mapping, size_t count, float left, float baseline);

#ifdef __cplusplus
}
#endif

#endif /* FONT_CHEF_CHARACTER_MAPPING_H */
