#ifndef UTF8_DECODE_DFA_H
#define UTF8_DECODE_DFA_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum utf8_decode_dfa_result {
  utf8_decode_dfa__accept = 0,
  utf8_decode_dfa__reject = 1,
  utf8_decode_dfa__result_max = UINT32_MAX
};

enum utf8_decode_dfa_result dfa(
  enum utf8_decode_dfa_result state,
  uint32_t * codep,
  uint32_t byte
);

#ifdef __cplusplus
}
#endif

#endif /* UTF8_DECODE_DFA_H */
