#ifndef __FS_FONT_H__
#define __FS_FONT_H__

#include "FS_stb_truetype.h"
#include "FS_Vector2.h"
#include "FS_Texture2D.h"

typedef struct
{
	stbtt_bakedchar chars[96];
	uint32_t firstChar;
	uint32_t charCount;
	Bitmap2D bitmap;
	float pixelHeight;

	uint32_t textureID;
} TrueTypeFont;

#endif // __FS_FONT_H__