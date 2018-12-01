#ifndef __UTF8_H__
#define __UTF8_H__

/* for size_t */
#include <stdlib.h>

/* for char32_t */
#include <uchar.h>

/* for uint8_t */
#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/* encode */
size_t utf8_encode_length(char32_t value);
size_t utf8_encode(char32_t in, uint8_t *out);

/* decode */
size_t utf8_decode_length(uint8_t first_byte);
size_t utf8_decode(const uint8_t *in, char32_t *out);

#ifdef __cplusplus
}
#endif

#endif	/* __UTF8_H__ */
