#ifndef __UTF16_H__
#define __UTF16_H__
 
// for char16_t and char32_t 
#include <uchar.h>
 
// for size_t
#include <stdlib.h>
 
#ifdef __cplusplus
extern "C" {
#endif
 
// encode
size_t utf16_encode_length(char32_t value);
size_t utf16_encode(char32_t in, char16_t *out);
 
// decode
size_t utf16_decode_length(char16_t first_word);
size_t utf16_decode(const char16_t *in, char32_t *out);
 
#ifdef __cplusplus
}
#endif
 
#endif	// __UTF16_H__

