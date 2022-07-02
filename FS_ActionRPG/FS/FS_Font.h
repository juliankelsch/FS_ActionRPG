#ifndef __FS_FONT_H__
#define __FS_FONT_H__

#include "FS_stb_truetype.h"
#include "FS_Vector2.h"
#include "FS_Texture2D.h"

#include <stdbool.h>

typedef struct
{
	stbtt_bakedchar chars[96];
	uint32_t firstChar;
	uint32_t charCount;
	Bitmap2D bitmap;
	float pixelHeight;
	float centerY;

	uint32_t textureID;

} TrueTypeFont;

typedef struct
{
	float x0, y0, s0, t0;
	float x1, y1, s1, t1;
} CharacterQuad;

typedef enum
{
	FontStyle_Normal,
	FontStyle_Bold,
	FontStyle_Italic,
	FontStyle_BoldItalic,

	FontStyle_Count
} FontStyle;

typedef union
{
	TrueTypeFont fonts[FontStyle_Count];
	struct
	{
		TrueTypeFont normal;
		TrueTypeFont bold;
		TrueTypeFont italic;
		TrueTypeFont boldItalic;
	};
} FontFamily;

void TrueTypeFont_GetQuad(TrueTypeFont *font, float *x, float *y, char c, float charSpacing, CharacterQuad *quad);
void TrueTypeFont_GetXAdvance(TrueTypeFont *font, char c);
bool TrueTypeFont_HasChar(TrueTypeFont *font, char c);
float TrueTypeFont_CalculateCenterOffsetY(TrueTypeFont *font);

#endif // __FS_FONT_H__