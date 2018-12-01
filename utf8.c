#include "utf8.h"

size_t utf8_encode_length(char32_t value)
{
	if (value <= 0x7F) {
		return 1;	
	} else if (value <= 0x7FF) {
		return 2;	
	} else if (value <= 0xFFFF) {
		return 3;	
	} else if (value <= 0x10FFFF) {
		return 4;	
	}

	/* out of range */
	return 0;
}

size_t utf8_encode(char32_t in, uint8_t *out)
{
  size_t len = utf8_encode_length(in);
 
    switch (len) {
        case 1:
            out[0] = in & 0x7F;
            return 1;
        case 2:
            out[0] = 0xC0 | ((in >> 6) & 0x1F);
            out[1] = 0x80 | ((in >> 0) & 0x3F);
            return 2;
        case 3:
            out[0] = 0xE0 | ((in >> 12) & 0x0F);
            out[1] = 0x80 | ((in >>  6) & 0x3F);
            out[2] = 0x80 | ((in >>  0) & 0x3F);
            return 3;
        case 4:
            out[0] = 0xF0 | ((in >> 18) & 0x07);
            out[1] = 0x80 | ((in >> 12) & 0x3F);
            out[2] = 0x80 | ((in >>  6) & 0x3F);
            out[3] = 0x80 | ((in >>  0) & 0x3F);
            return 4;
    }

    /* out of range */
	return 0;
}

size_t utf8_decode_length(uint8_t first_byte)
{
#if 0
/* 方法一 */
	if ((first_byte & 0xF8) == 0xF0) {
		return 4;
	}

	if ((first_byte & 0xF0) == 0xE0) {
		return 3;
	}

	if ((first_byte & 0xE0) == 0xC0) {
		return 2;
	}

	if ((first_byte & 0x80) == 0) {
		return 1;   /* ASCII */
	}

	return 0;
#else
/* 方法二 */
    if (first_byte < 0x80) {
        return 1;   
    } else if (first_byte < 0xE0) {
        return 2;   
    } else if (first_byte < 0xF0) {
        return 3;   
    } else if (first_byte < 0xF8) {
        return 4;   
    }
    /* out of range */
    return 0;
#endif
}

size_t utf8_decode(const uint8_t *in, char32_t *out)
{
	size_t len = utf8_decode_length(in[0]);

	switch (len) {
		case 1:
			*out = in[0];
			return 1;
		case 2:
			*out = (in[0] & 0x1F) << 6;
			*out += in[1] & 0x3F;
			return 2;
		case 3:
			*out = (in[0] & 0x0F) << 12;
			*out += (in[1] & 0x3F) << 6;
			*out += in[2] & 0x3F;
			return 3;
		case 4:
			*out = (in[0] & 0x07) << 18;
			*out += (in[1] & 0x3F) << 12;
			*out += (in[2] & 0x3F) << 6;
			*out += in[3] & 0x3F;
			return 4;
		default:
			return 0;
	}

	/* out of range */
	return 0;
}

