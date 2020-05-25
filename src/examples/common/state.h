#ifndef FONT_CHEF_EXAMPLE_STATE_H
#define FONT_CHEF_EXAMPLE_STATE_H

#include "SDL.h"
#include "font-chef/rect.h"
#include "font-chef/size.h"
#include "font-chef/color.h"

#if __cplusplus
extern "C" {
#endif


struct state {
  SDL_Window * window;
  SDL_Renderer * renderer;
  struct fc_rect bounds;
};

struct texture;

void init(struct state * state);
uint8_t update(struct state * state);
void quit(struct state * state);
struct texture * texture_make(struct state const * state, void * pixels, struct fc_size size);
void texture_destroy(struct texture * texture);
void render(struct texture * texture, struct fc_rect clip, struct fc_rect target);

#if __cplusplus
}
#endif

#endif
