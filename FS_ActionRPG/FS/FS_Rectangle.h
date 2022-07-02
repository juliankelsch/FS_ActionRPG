#ifndef __FS_RECTANGLE_H__
#define __FS_RECTANGLE_H__

#include <stdint.h>

typedef struct
{
	float x, y, width, height;
} Rect;

typedef struct
{
	int32_t x, y, width, height;
} RectInt;

typedef struct
{
	float top, left, bot, right;
} RectOffsets;

Rect Rect_GetOffsetRect(Rect rect, RectOffsets offsets);

#endif // __FS_RECTANGLE_H__