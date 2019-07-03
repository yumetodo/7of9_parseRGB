#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

bool parseRGB(char *srcPtr, uint8_t *Red, uint8_t *Green, uint8_t *Blue)
{
	if (strlen(srcPtr) != 6) {
		return false;
	}
	char *endptr;
	int16_t val = strtol(srcPtr, &endptr, 16);
	if (*endptr != 0x00) {
		return false;
	}
	*Red = (uint8_t)((val & 0xFF0000) / 0x10000);
	*Green = (uint8_t)((val & 0xFF00) / 0x100);
	*Blue = (uint8_t)((val & 0xFF));
	return true;
}
