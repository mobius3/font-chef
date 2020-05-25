#include "font-chef/font-chef.h"
#include "SDL.h"

#include "common/state.h"
#include "common/font.h"

int main(int argc, char const ** argv) {
  struct state state = {};
  init(&state);

  struct fc_font * font = fc_construct(font_pacifico_ttf.data, fc_pt(30), fc_color_white);
  fc_add(font, fc_basic_latin.first, fc_basic_latin.last);
  fc_cook(font);

  struct texture * font_texture = texture_make(
      &state,
      fc_get_pixels(font)->data,
      fc_get_pixels(font)->dimensions
  );

  struct fc_character_mapping mapping[256];
  const char text[] = "Hello, handsome! I mean... world!";
  int txt_glyph_count = fc_render_wrapped(
      font,
      (uint8_t *) text,
      strlen(text),
      state.bounds.right * 0.66f,
      1.0f,
      fc_align_left, mapping
  );
  fc_move(mapping, txt_glyph_count, 0.0f, state.bounds.bottom / 2 - 20);

  while (update(&state)) {
    for (int i = 0; i < txt_glyph_count; i++) {
      render(font_texture, mapping[i].source, mapping[i].target);
    }
  }

  fc_destruct(font);
  texture_destroy(font_texture);
  quit(&state);
  return 0;
}