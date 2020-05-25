#ifndef FONT_CHEF_FONT_CHEF_H
#define FONT_CHEF_FONT_CHEF_H

/**
 * @file font-chef.hpp
 * Main include file
 */

/**
 @mainpage Welcome!

 Font Chef is a cross-platform C99 library to create character atlas of pre-rasterized glyphs from a font at a specified size and color. It is mostly useful in situations where you cannot afford to rasterize a piece of text again whenever it changes.

 It abstracts [stb_truetype](https://github.com/nothings/stb/blob/master/stb_truetype.h) to render glyphs to a pixmap and to produce appropriate clipping rects to later display those glyphs.

 Features

 - Small, clean and easy-to-use API
 - Ships with C++ wrapper classes
 - Considers kerning when resolving rendering rects
 - Ships with many standard unicode blocks to choose from
 - Rendering API agnostic (it does not render anything directly, it returns pixels and clipping rects)
 - Fully documented with examples for each function
 - No external dependencies

 @subsection references Starting points
 - The <a href="modules.html">modules</a> section has functions and structs grouped
 - ::fc_construct, ::fc_add, ::fc_cook and ::fc_destruct are the main C functions
 - Check the [Unicode Character Database](ftp://ftp.unicode.org/Public/UNIDATA/Blocks.txt) for a list of unicode blocks
 */

#include "font.h"

#ifdef __cplusplus
#include "font.hpp"
#endif

#endif //FONT_CHEF_FONT_CHEF_H
