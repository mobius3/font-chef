#include <stdint.h>
#include <stddef.h>
#include "dfa.h"

struct utf8_decode_result {
  uint32_t codepoint;
  uint32_t skip;
};

struct utf8_decode_result utf8_decode(unsigned char const * text, size_t text_len) {
  struct utf8_decode_result point = {0, 0};
  enum utf8_decode_dfa_result state = utf8_decode_dfa__accept;

  do {
    state = dfa(state, &point.codepoint, (uint32_t) text[point.skip]);
    point.skip++;
  } while (
    state != utf8_decode_dfa__accept &&
    state != utf8_decode_dfa__reject &&
    point.skip < text_len
  );
  if (state == utf8_decode_dfa__reject) point.skip = 0;
  return point;
}