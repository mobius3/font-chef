#include "font-chef/font-chef.hpp"
#include "common/font.h"
#include "common/state.hpp"

int main(int argc, char const ** const argv) {
  xx::state state;

  fc::font font = fc
      ::from(font_pacifico_ttf.data, fc_pt(30), fc_color_white)
      .add(fc_basic_latin)
      .cook();

  xx::texture font_texture = state.texture(font.pixels());
  fc::render_result result = font
      .render("Hello, handsome! I mean... world!")
      .wrap(state.bounds().right * 0.66f)
      .move(0.0f, state.bounds().bottom / 2 - 20);
  while (state.update()) {
    for (auto & map : result) {
      font_texture.render(map.source, map.target);
    }
  }

  return 0;
}
