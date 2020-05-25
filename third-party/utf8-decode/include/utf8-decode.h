#ifndef UTF8_DECODE_H
#define UTF8_DECODE_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct utf8_decode_result {
  uint32_t codepoint;
  uint32_t skip;
};

extern struct utf8_decode_result utf8_decode(unsigned char const * text, size_t text_len);

#ifdef __cplusplus
}
#endif

#endif /* UTF8_DECODE_H */
