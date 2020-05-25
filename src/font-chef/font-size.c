#include "font-chef/font-size.h"

struct fc_font_size fc_pt(float value) {
  struct fc_font_size result = {value, fc_size_type__pt};
  return result;
}

struct fc_font_size fc_px(float value) {
  struct fc_font_size result = {value, fc_size_type__px};
  return result;
}
