#ifndef __FS_TEXTURE2D_H__
#define __FS_TEXTURE2D_H__

#include "FS_Color.h"
#include "FS_Arena.h"

typedef struct
{
	uint16_t width, height;
	Color *pixels;
} Texture2D;

typedef struct
{
	uint16_t width, height;
	uint8_t *pixels;
} Bitmap2D;

Texture2D Texture2D_Create(Arena *arena, uint16_t width, uint16_t height);
Texture2D Texture2D_CreateCircle(Arena *arena, uint16_t size, float innerRadius, float outerRadius);

#endif  __FS_TEXTURE2D_H__