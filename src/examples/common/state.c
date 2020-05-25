#include "state.h"

struct texture {
  SDL_Renderer * renderer;
  SDL_Texture * texture;
};

void init(struct state * state) {
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);
  state->bounds.top = 0;
  state->bounds.left = 0;
  state->bounds.right = 384;
  state->bounds.bottom = 216;
  state->window = SDL_CreateWindow("Font Chef!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 384, 216, SDL_WINDOW_RESIZABLE);
  state->renderer = SDL_CreateRenderer(state->window, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawColor(state->renderer, 40, 44, 52, 255);
}

uint8_t update(struct state * state) {
  static int w = 0, h = 0;
  SDL_GetWindowSize(state->window, &w, &h);
  SDL_RenderPresent(state->renderer);
  SDL_Delay(1);
  SDL_PumpEvents();
  state->bounds.right = (float) w;
  state->bounds.bottom = (float) h;
  SDL_RenderClear(state->renderer);
  return !SDL_QuitRequested();
}

void quit(struct state * state) {
  SDL_DestroyRenderer(state->renderer);
  SDL_DestroyWindow(state->window);
  SDL_Quit();
}

static SDL_Texture * create_sdl2_texture(
    SDL_Renderer * renderer,
    unsigned char * pixel_data,
    struct fc_size dimensions
) {
  Uint32 rmask, gmask, bmask, amask;
  int x = (int) dimensions.width, y = (int) dimensions.height;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  rmask = 0xff000000;
  gmask = 0x00ff0000;
  bmask = 0x0000ff00;
  amask = 0x000000ff;
#else
  rmask = 0x000000ff;
  gmask = 0x0000ff00;
  bmask = 0x00ff0000;
  amask = 0xff000000;
#endif

  SDL_Surface * surface = SDL_CreateRGBSurfaceFrom(
      (void *) pixel_data,
      x, y, 32, x * 4, rmask, gmask, bmask, amask
  );
  SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_NONE);

  if (surface == NULL) {
    return NULL;
  }

  SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (texture != NULL) {
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
  }
  SDL_FreeSurface(surface);
  return texture;
}

struct texture * texture_make(struct state const * state, void * pixels, struct fc_size size) {
  if (!pixels || !state) return NULL;
  struct texture * texture_p = malloc(sizeof *texture_p);
  texture_p->texture = create_sdl2_texture(state->renderer, pixels, size);
  texture_p->renderer = state->renderer;
  return texture_p;
}

void texture_destroy(struct texture * texture) {
  SDL_DestroyTexture(texture->texture);
  free(texture);
}

void render(struct texture * texture, struct fc_rect clip, struct fc_rect target) {
  SDL_Rect src = {
      .x = (int) clip.left,
      .y = (int) clip.top,
      .w = (int) fc_rect_width(&clip),
      .h = (int) fc_rect_height(&clip)
  };
  SDL_Rect dst = {
      .x = (int) target.left,
      .y = (int) target.top,
      .w = (int) fc_rect_width(&target),
      .h = (int) fc_rect_height(&target)
  };
  SDL_RenderCopy(texture->renderer, texture->texture, &src, &dst);
}

void rect_center_in(struct fc_rect const * bounds, struct fc_rect * rect) {
  float bounding_width = fc_rect_width(bounds),
        rect_width = fc_rect_width(rect),
        bounding_height = fc_rect_height(bounds),
        rect_height = fc_rect_height(rect);
  rect->left = bounds->left + (bounding_width - rect_width) / 2;
  rect->right = rect->left + rect_width;
  rect->top = bounds->top + (bounding_height - rect_height) / 2;
  rect->bottom = rect->top + rect_height;
}

void render_rect(struct state * state, struct fc_rect const * rect, struct fc_color color) {
  uint8_t r, g, b, a;
  SDL_GetRenderDrawColor(state->renderer, &r, &g, &b, &a);
  SDL_SetRenderDrawColor(state->renderer, color.r, color.g, color.b, color.a);
  SDL_Rect dst = {
      .x = (int) rect->left,
      .y = (int) rect->top,
      .w = (int) fc_rect_width(rect),
      .h = (int) fc_rect_height(rect)
  };
  SDL_RenderDrawRect(state->renderer, &dst);
  SDL_SetRenderDrawColor(state->renderer, r, g, b, a);
}
