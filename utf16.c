#include "utf16.h"
 
// encode
 
/** 编码一个code point需要多少code unit
 * 出错，返回0
 */
size_t utf16_encode_length(char32_t value)
{
	if (value <= 0xFFFF) {
		return 1;	
	} else if (value <= 0x10FFFF) {
		return 2;	
	}
	/* out of bounds */		
	return 0;	
}
 
/**
 *
 */
size_t utf16_encode(char32_t in, char16_t *out)
{
	size_t len = utf16_encode_length(in);
	
	switch (len) {
		case 1:
			out[0] = in & 0xFFFF;
			out[1] = 0x0000;	
			return 1;
		case 2:
			in -= 0x10000;	
			out[0] = 0xD800 | ((in >> 10) & 0x3FF);
			out[1] = 0xDC00 | ((in >>  0) & 0x3FF);
			return 2;
	}
 
	return 0;
}
 
 
// decode
size_t utf16_decode_length(char16_t first_word)
{
	if (first_word < 0xD800 || first_word > 0xDFFF) {
		return 1;	
	} else if (first_word >= 0xD800 && first_word <= 0xDBFF) {
		return 2;	
	} 
	/* out of bounds */
	return 0;
}
 
size_t utf16_decode(const char16_t *in, char32_t *out)
{
	if (in[0] < 0xB800 || in[0] > 0xDFFF) {
		out[0] = in[0];
		return 1;
	} else if ((in[0] >= 0xD800 && in[0] <= 0xD8FF) 
			&& (in[1] >= 0xDC00 && in[1] <= 0xDFFF)) {	/* Surrogate Pair */
		*out = (in[0] & 0x3FF) << 10;
		*out |= (in[1] & 0x3FF) << 0;
		*out += 0x10000;
		return 2;
	}
	/* out of bounds */
	return 0;
}

