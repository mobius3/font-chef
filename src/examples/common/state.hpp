#ifndef FONT_CHEF_EXAMPLE_STATE_HPP
#define FONT_CHEF_EXAMPLE_STATE_HPP

#include "state.h"

namespace xx {

  class texture {
    ::texture * data;

    public:
      texture(::state * state, void * pixels, fc_size size) : data(::texture_make(state, pixels, size))
        { };

      ~texture() {
        ::texture_destroy(data);
      }
      texture(texture && other) noexcept : data(other.data) {
        other.data = nullptr;
      }

     void render(fc_rect clip, fc_rect target) {
        ::render(data, clip, target);
      }
  };

  class state {
      ::state data;

    public:
      state() : data({}) {
        ::init(&data);
      };

      ~state() {
        ::quit(&data);
      }

      uint8_t update() {
        return ::update(&data);
      }

      fc_rect bounds() const {
        return data.bounds;
      }

      xx::texture texture(fc_pixels const & pixels) {
        return xx::texture(&data, pixels.data, pixels.dimensions);
      }
  };
};

#endif
