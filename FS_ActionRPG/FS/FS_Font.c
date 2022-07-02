#include "FS_Font.h"
#include "FS_Mathf.h"

void TrueTypeFont_GetQuad(TrueTypeFont *font, float *x, float *y, char c, float charSpacing, CharacterQuad *quad)
{
	stbtt_GetBakedQuad(font->chars, font->bitmap.width, font->bitmap.height, c - font->firstChar, x, y, (stbtt_aligned_quad*)quad, 1, charSpacing);
}

void TrueTypeFont_GetXAdvance(TrueTypeFont *font, char c)
{
	return font->chars[c - font->firstChar].xadvance;
}

bool TrueTypeFont_HasChar(TrueTypeFont *font, char c)
{
	return c >= font->firstChar && c < (font->firstChar + font->charCount);
}

float TrueTypeFont_CalculateCenterOffsetY(TrueTypeFont *font)
{
	float min = Mathf_Infinity;
	float max = Mathf_NegativeInfinity;
	for (size_t i = 0; i < font->charCount; i++)
	{
		stbtt_bakedchar *c = font->chars + i;
		max = Mathf_Max(max, c->yoff - (c->y1 - c->y0));
		min = Mathf_Min(min, c->yoff);
	}
	return (max + min) / 2.0f;
}

