#ifndef FONT_CHEF_FONT_H
#define FONT_CHEF_FONT_H

/**
 * @file font.h
 * This file contains the structure fc_font which is the core of the font-chef library.
 *
 * @defgroup font Font
 * All the functions and types that deal with fonts and font-cooking
 */

#include <stdlib.h>
#include <stdint.h>

#include "font-chef/font-chef-export.h"
#include "font-chef/unicode-block.h"
#include "font-chef/font-size.h"
#include "font-chef/character-mapping.h"
#include "font-chef/color.h"
#include "font-chef/size.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief A structure holding pixel data and its dimensions
 *
 * This is the return type of ::fc_get_pixels and has valid data after ::fc_cook was called.
 *
 * @sa ::fc_get_pixels
 * @sa ::fc_cook
 * */
struct fc_pixels {
  /**
   * @brief The pixel data produced after ::fc_cook, a 4-byte-per-pixel RGBA bitmap.
   */
  unsigned char * data;

  /**
   * @brief Width and height of this pixel data. Buffer size would be dimensions.width * dimensions.height * 4
   */
  struct fc_size dimensions;
};


/**
 * @struct fc_font
 * @brief A fc_font struct represents all data and metadata about a font.
 * @ingroup font
 *
 * It is an opaque structure. Consult ::fc_construct for more information.
 */
 struct fc_font;

/**
 * @brief Constructs a `fc_font` structure with the provided font,
 * a size (either in pixels or points) and a font color in RGBA.
 * @ingroup font
 *
 * It does not have any pixel data yet, you
 * need to call `::fc_add` to add unicode ranges and `::fc_cook` to produce a 4 byte-per-pixel,
 * RGBA, bitmap.
 *
 * **Example**
 * @code
 * // fully reads a file to memory and returns a pointer to it
 * uint8_t * read_file(char const * path);
 *
 * void main() {
 *     uint8_t * font_buffer = read_file("times.ttf"); // replace with real font path
 *     struct fc_font font;
 *     fc_construct(&font, font_buffer, fc_px(12), fc_color_red);
 *     // font is ready to be used
 * }
 * @endcode
 *
 * @param font_data A pointer to the in-memory font-data (it will NOT be managed
 *                  nor free'd by font-chef).
 * @param font_size A size either in pixels or points to apply when packing
 * @param font_color The color of the characters in the rendered bitmap
 */
FONT_CHEF_EXPORT extern struct fc_font * fc_construct(
  uint8_t const * font_data,
  struct fc_font_size font_size,
  struct fc_color font_color
);

/**
 * @brief Adds the given unicode range to the list of blocks to be cooked. You must
 * add blocks *before* calling `::fc_cook`.
 * @ingroup font
 *
 * Note that calling this function multiple times with the same block **will add
 * the same block again** (although resulting image won't have duplicated
 * blocks).
 *
 * Also note that no overlapping management is done.
 *
 * If you call this function *after* calling `::fc_cook`, you will need to call
 * `::fc_cook` again. It is advised not to do this, add all the ranges you
 * will be using before.
 *
 * **Example**
 * @code
 * void main() {
 *     struct fc_font font; // suppose already initialized with fc_construct
 *     fc_add(&font, fc_unicode_block_basic_latin.fist, fc_unicode_block_basic_latin.last);
 *     fc_add(&font, fc_unicode_block_latin_1_supplement.fist, fc_unicode_block_latin_1_supplement.last);
 *     // font is ready for `fc_cook`
 * }
 * @endcode
 *
 * @param font A pointer to the `fc_font` instance
 * @param first The first unicode point in this block
 * @param last The last unicode point in this block
 */
FONT_CHEF_EXPORT extern void fc_add(
  struct fc_font * font,
  uint32_t first,
  uint32_t last
);

/**
 * @brief Generates a bitmap and corresponding character information for a font.
 * @ingroup font
 *
 * It uses all blocks added with `::fc_add` to generate a bitmap that later can
 * be used to render text with `::fc_render`. You *must* call `::fc_add` before
 * calling this function.
 *
 * If you call `::fc_add` after calling this function, you will need to call
 * call it again. It is advisable to call `::fc_cook` just once.
 *
 * **Example**
 * @code
 * // suppose this creates a 4bpp texture from pixel data
 * void * create_texture(void * pixel_data, size_t width, size_t height);
 *
 * void main() {
 *     struct fc_font font; // suppose `fc_construct` and `fc_add` was called
 *     fc_cook(&font);
 *     void * texutre = create_texture(
 *         font.pixels.data,
 *         font.pixels.dimensions.width,
 *         font.pixels.dimensions.height
 *     );
 *     // now you're ready for `fc_render`
 * }
 * @endcode
 *
 * @param font A pointer to a `fc_font` value to generate pixels and mapping
 */
FONT_CHEF_EXPORT extern void fc_cook(struct fc_font * font);

/**
 * @brief Produces a list of source and target rectangles that can be used as clipping
 * rects (or UV maps) for the source texture and as target space coordinates.
 * @ingroup font
 *
 * This function uses data produced by `fc_cook` and
 * information inside the font data to map all the characters passed in
 * to a list of source and target coordinates. It also takes in consideration the kerning
 * for each character pair.
 *
 * Also observe that the source and target rect is in pixel coordinates (from 0,0 to w,h),
 * not from 0 to 1
 *
 * ** Adjusting baseline **
 * Baseline is the line (a `y` coordinate) that the characters will extend *above* and *below* it (e.g, observe the letter "g").
 * Font Chef produces destination rectangles with a baseline `y = 0`. This means that before rendering, you will have to add the
 * desired baseline to both `top` and `bottom` values of the destination rectangle.
 *
 * **Example**
 * @code
 * // suppose a function that renders a texture clipped by `src` at coordinates `dst`
 * void render_clip(void * texture, fc_rect src, fc_rect dst);
 *
 * void main() {
 *     struct fc_font font; // suppose `fc_construct`, `fc_add` and `fc_cook` already called
 *     void * texture; // suppose texture created as in `fc_cook` examples
 *     struct fc_character_mapping mapping[13];
 *     char const * hello_world = "Hello, World!";
 *     int glyph_count = fc_render(&font, hello_world, 13, &mapping);
 *     for (int i = 0; i < glyph_count; ++i) {
 *        render_clip(texture, mapping[i].source, mapping[i].destination);
 *     }
 * }
 * @endcode
 *
 * @param font A pointer to a `fc_font` value that will be used
 * @param text A pointer to a character array containing the text to map
 * @param byte_count How many bytes are there in the character array
 * @param mapping An array of `fc_character_mapping` values that
 *                       must be at least `byte_count` long.
 * @return the actual number of glyphs to be rendered.
 */
FONT_CHEF_EXPORT extern int fc_render(
  struct fc_font const * font,
  unsigned char const * text,
  size_t byte_count,
  struct fc_character_mapping * mapping
);

/**
 * @brief A shortcut for rendering and then wrapping the result.
 * @ingroup font
 *
 * This function is a shorthand for calling ::fc_render and ::fc_wrap in sequence. It uses
 * vertical metrics contained in the font to automatically deduce the font's default line height.
 * See the documentation for ::fc_wrap for more information about wrapping.
 *
 * @param font A pointer to a `fc_font` value that will be used
 * @param text A pointer to a character array containing the text to map
 * @param byte_count How many bytes are there in the character array
 * @param line_width The maximum line width, in target/screen size (e.g, pixels)
 * @param line_height_multiplier A value that can be used to increase the line height/spacing
 * @param alignment Which aligment should lines follow
 * @param mapping An array of `fc_character_mapping` values that
 *                       must be at least `byte_count` long.
 * @sa ::fc_render
 * @sa ::fc_wrap
 * @sa fc::render_result::wrap
 */
FONT_CHEF_EXPORT int fc_render_wrapped(
    struct fc_font const * font,
    unsigned char const * text,
    size_t byte_count,
    size_t line_width,
    float line_height_multiplier,
    enum fc_alignment alignment,
    struct fc_character_mapping * mapping
);

/**
 * @brief Destroys and frees all memory allocated by this library.
 * @ingroup font
 *
 * You *must* call this once done with a `fc_font` value else your memory will leak. Using it beyond this
 * point will most likely cause segmentation fault.
 *
 * @param font Pointer to the `fc_font` value that will be destroyed.
 */
FONT_CHEF_EXPORT extern void fc_destruct(struct fc_font * font);

/**
 * @brief Returns the font size set to this font at construction time
 * @ingroup font
 *
 * There is no function to set a font size because setting it
 * after cooking has no effect, and sure enough someone would try it and file
 * a bug report.
 *
 * @param font A pointer to a `fc_font` value to get the size from
 * @return The font size specified
 */
FONT_CHEF_EXPORT extern struct fc_font_size fc_get_font_size(struct fc_font const * font);


/**
 * @brief Returns the font color set to this font at construction time
 * @ingroup font
 *
 * There is no function to set a font color because setting it
 * after cooking has no effect, and sure enough someone would try it and file
 * a bug report.
 *
 * @param font A pointer to a `fc_font` value to get the color from
 * @return The color specified
 */
FONT_CHEF_EXPORT extern struct fc_color fc_get_color(struct fc_font const * font);

/**
 * @brief Returns the font data specified in fc_construct
 * @ingroup font
 * @warning Font-cache does not know the font data buffer size (because it is irrelevant to it) so it is impossible to return it.
 * @param font The font to get the font data from
 * @return The font data
 */
FONT_CHEF_EXPORT extern uint8_t const * fc_get_font_data(struct fc_font const * font);


/**
 * @brief Returns count of added blocks in this font
 * @ingroup font
 * @param font The font to get the packed blocks count from
 * @return The count of added blocks
 */
FONT_CHEF_EXPORT extern size_t fc_get_block_count(struct fc_font const * font);


/**
 * @brief Returns a unicode block at the index position
 * @ingroup font
 * @param font The font to get the packed block from
 * @param index The pack block index
 * @return A `fc_unicode_block` value containing the block information
 */
FONT_CHEF_EXPORT extern struct fc_unicode_block fc_get_block_at(struct fc_font const * font, size_t index);

/**
 * @brief Returns the pixel data after for a font generated after a ::fc_cook was called
 * @ingroup font
 * @param font The font to get the pixel data from
 * @return A value of ::fc_pixels
 */
FONT_CHEF_EXPORT extern struct fc_pixels const * fc_get_pixels(struct fc_font const * font);

/**
 * @brief Returns the space glyph width and height for this font at its specified size
 * @ingroup font
 *
 * It considers both the left side bearing (space after previous character) and the actual
 * glyph height. This is mostly useful when doing wrapping calculations.
 *
 * @param font The font to get the space metrics from
 * @return The width and height of a space glyph
 */
FONT_CHEF_EXPORT extern struct fc_size fc_get_space_metrics(struct fc_font const * font);

#ifdef __cplusplus
}
#endif

#endif
