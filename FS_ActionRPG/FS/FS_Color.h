#ifndef __FS_COLOR_H__
#define __FS_COLOR_H__

#include <stdint.h>

typedef struct
{
	uint8_t r, g, b, a;
} Color;

Color Color_RGB(float red, float green, float blue);
Color Color_RGBA(float red, float green, float blue, float alpha);

#endif //  __FS_COLOR_H__
