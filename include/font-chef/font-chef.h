#ifndef FONT_CHEF_FONT_CHEF_H
#define FONT_CHEF_FONT_CHEF_H

/**
 * @file font-chef.hpp
 * Main include file
 */

/**
 @mainpage Welcome!

 Font Chef is a cross-platform C99 and C++ library to create character atlas of pre-rasterized glyphs from a font at a specified size and color. It is mostly useful in situations where you cannot afford to rasterize a piece of text again whenever it changes.

 It abstracts [stb_truetype](https://github.com/nothings/stb/blob/master/stb_truetype.h) to render glyphs to a pixmap and to produce appropriate clipping rects to later display those glyphs.


<b>Hello world in C++</b>
@code
fc::font font = fc::from(font_data, fc::px(30), fc_color_black).add(fc_basic_latin).cook();
// use font.pixels() to make a texture
fc::render_result result = font.render("Hello, world!");
for (auto & map : result) {
    render(texture, map.source, map.target);
}
@endcode

<b>Hello world in C</b>
@code
fc_font * font = fc_construct(font_data, fc_px(30), fc_color_black);
fc_add(fc_basic_latin.start, fc_basic_latin.end);
fc_cook(font);
// use fc_get_pixels(font) to make a texture

const char hello[] = "Hello, world!";
fc_character_mapping output[32];
int count = fc_render(font, text, strlen(hello), output);
for (int i = 0; i < count; i++) {
    render(texture, output[i].source, output[i].target
}
@endcode

 <b>Features</b>

 - Small, clean and easy-to-use API
 - Ships with @ref cpp wrapper classes
 - Considers kerning when resolving rendering rects
 - Ships with many standard unicode blocks to choose from
 - Rendering API agnostic (it does not render anything directly, it returns pixels and clipping rects)
 - Fully documented with examples for each function
 - No external dependencies

 @subsection references Starting points
 - The @ref manual page describes the core functionality of Font Chef
 - The <a href="modules.html">modules</a> section has functions and structs grouped by type
 - Check the [Unicode Character Database](ftp://ftp.unicode.org/Public/UNIDATA/Blocks.txt) for a list of unicode blocks
 */

#include "font.h"

#ifdef __cplusplus
#include "font.hpp"
#endif

#endif //FONT_CHEF_FONT_CHEF_H
