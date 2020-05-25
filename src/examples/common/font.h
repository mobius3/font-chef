#ifndef c_rez_font_font_h
#define c_rez_font_font_h

#ifdef __cplusplus
extern "C" {
#endif

#ifndef c_rez_resource_struct
#define c_rez_resource_struct
typedef struct c_rez_resource {
  unsigned char const * const data;
  unsigned int const length;
} c_rez_resource;
#endif /* c_rez_resource_struct */

extern c_rez_resource const font_pacifico_ttf;
struct c_rez_resource const * c_rez_locate_font(const char name[]);
#ifdef __cplusplus
}
#endif

#endif /* c_rez_font_font_h */

