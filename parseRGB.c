#include "parseRGB.h"
#include <string.h>
static uint8_t parse(char c)
{
    if (u8"0"[0] <= c && c <= u8"9"[0]) return c - u8"0"[0];
    if (u8"a"[0] <= c && c <= u8"f"[0]) return c - u8"a"[0] + 10;
    if (u8"A"[0] <= c && c <= u8"F"[0]) return c - u8"A"[0] + 10;
    return 0xFF;
}
bool parseRGB(const char *srcPtr, uint8_t *Red, uint8_t *Green, uint8_t *Blue)
{
    if(NULL == srcPtr || NULL == Red || NULL == Green || NULL == Blue) return false;
	if (strlen(srcPtr) != 6) {
		return false;
	}
    uint8_t re[6];
    for(size_t i = 0; i < 6; ++i) if (0xFF == (re[i] = parse(srcPtr[i]))) return false;
    for(size_t i = 0; i < 6; i += 2) re[i] = re[i] << 4;
    *Red = re[0] + re[1];
    *Green = re[2] + re[3];
    *Blue = re[4] + re[5];
}
