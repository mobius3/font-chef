#include "font-chef/rect.h"

float fc_rect_width(struct fc_rect const * rect) {
  return rect->right - rect->left;
}

float fc_rect_height(struct fc_rect const * rect) {
  return rect->bottom - rect->top;
}

