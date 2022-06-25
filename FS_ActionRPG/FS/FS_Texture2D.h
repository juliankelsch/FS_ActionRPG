#ifndef __FS_TEXTURE2D_H__
#define __FS_TEXTURE2D_H__

#include "FS_Color.h"

typedef struct
{
	uint16_t width, height;
	Color *pixels;
} Texture2D;

#endif  __FS_TEXTURE2D_H__