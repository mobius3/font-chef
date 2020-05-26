# Font Chef

*Font Chef* is a cross-platform C99 and C++ library to create character atlas of pre-rasterized glyphs from a font at a specified size and color. It is mostly useful in situations where you cannot afford to rasterize a piece of text again whenever it changes.

It abstracts [stb_truetype](https://github.com/nothings/stb/blob/master/stb_truetype.h) to render glyphs to a pixmap and to produce appropriate clipping rects to later display those glyphs.

**Hello world in C++**
```c++
fc::font font = fc::from(font_data, fc::px(30), fc_color_black).add(fc_basic_latin).cook();
fc::render_result result = font.render("Hello, world!");
// use font.pixels() to make a texture
for (auto & map : result) {
    render(texture, map.source, map.target);
}
```

**Hello world in C**
```c
fc_font * font = fc_construct(font_data, fc_px(30), fc_color_black);
fc_add(fc_basic_latin.start, fc_basic_latin.end);
fc_cook(font);
// use fc_get_pixels(font) to make a texture

const char hello[] = "Hello, world!";
fc_character_mapping output[32];
int count = fc_render(font, text, strlen(hello), &output);
for (int i = 0; i < count; i++) {
    render(texture, output[i].source, output[i].target
}
```

**Features**

- Small, clean and easy-to-use API
- Ships with C++ wrapper classes
- Considers kerning when resolving rendering rects
- Ships with many standard unicode blocks to choose from
- Rendering API agnostic (it does not render anything directly, it returns pixels and clipping rects)
- Fully documented with examples for each function
- No external dependencies

## Integrating with your code

### Using pre-built releases

Download a pre-built release package suitable for your platform and
uncompress it somewhere you'll remember later (usually where you put
other development libraries). Let's assume you uncompressed font-chef to
`/home/me/libs/font-chef`.

**Using CMake**: If you're using CMake, specify the variable
`CMAKE_PREFIX_PATH` to point to it before running CMake in your project:

```shell script
cmake -DCMAKE_PREFIX_PATH=/home/me/libs
```

Afterwards you can use `find_package(font-chef)` and
`target_link_libraries(<your-executable> PUBLIC font-chef)` to link
`<your-executable>` against font-chef.

**Not using CMake**: Assuming you uncompressed font-chef to the same path as
above, you should configure your build system to look for include files
inside `/home/me/libs/font-chef/include` and to look for shared objects to
link against inside `/home/me/libs/font-chef/lib`. In case of Windows, you
should also point your linker to `font-chef/bin` as well.

### Using a source release and CMake

Uncompress font-chef in a folder inside your project (e.g,
`your-project/third-party/font-chef`) and then use
`add_subdirectory(third-party/font-chef EXCLUDE_FROM_ALL)` to add the
library target. Afterwards you can use `find_package(font-chef)` and
`target_link_libraries(<your-executable> PUBLIC font-chef)` to link
`<your-executable>` against font-chef.

Compiling the `.c` files directly in your project is not recommended nor
supported.

## Compile from source

You'll need CMake installed and in your path and also capable of finding
you compiler and linker. Then, after checking out this repository:

```shell script
mkdir build/
cd build/
cmake ..
make
```

## Examples

Examples for C and C++ are in the [src/examples](src/examples) folder. To build them, when running cmake as in [Compile from source](#compile-from-source), add the following variable:

```shell script
cmake .. -DFONT_CHEF_BUILD_EXAMPLES=1
```

You will need SDL2 available and CMake needs to be able to find it.

## Documentation

See [here](https://mobius3.github.io/font-chef)

