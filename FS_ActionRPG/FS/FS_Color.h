#ifndef __FS_COLOR_H__
#define __FS_COLOR_H__

#include <stdint.h>

typedef struct
{
	uint8_t r, g, b, a;
} Color;

#define Color_White (Color){255, 255, 255, 255}
#define Color_Black (Color){0, 0, 0, 255}
#define Color_Clear (Color){0, 0, 0, 0}
#define Color_Red (Color){255, 0, 0, 255}
#define Color_Green (Color){0, 255, 0, 255}
#define Color_Blue (Color){0, 0, 255, 255}
#define Color_Cyan (Color){0, 255, 255, 255}
#define Color_Yellow (Color){255, 255, 0, 255}
#define Color_Magenta (Color){255, 0, 255, 255}
#define Color_Orange (Color){255, 127, 0, 255}

Color Color_RGB(float red, float green, float blue);
Color Color_RGBA(float red, float green, float blue, float alpha);

#endif //  __FS_COLOR_H__
