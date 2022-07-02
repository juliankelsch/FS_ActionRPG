#include "FS_Assets.h"

#include "FS_Debug.h"

#include <stdio.h>

#define STB_TRUETYPE_IMPLEMENTATION
#include "FS_stb_truetype.h"

void Assets_FreeFont(TrueTypeFont *font)
{
	Assets_FreeBitmap(&font->bitmap);
}

void Assets_FreeFontFamily(FontFamily *font)
{
	for (size_t i = 0; i < FontStyle_Count; i++)
	{
		Assets_FreeBitmap(font->fonts + i);
	}
}

void Assets_FreeAny(void *buffer)
{
	free(buffer);
}

void Assets_FreeFile(Buffer *buffer)
{
	free(buffer->data);
	buffer->size = 0;
	buffer->data = NULL;
}

void Assets_FreeBitmap(Bitmap2D *bitmap)
{
	free(bitmap->pixels);
	bitmap->height = 0;
	bitmap->width = 0;
	bitmap->pixels = NULL;
}

void Assets_FreeTexture2D(Texture2D *texture)
{
	free(texture->pixels);
	texture->height = 0;
	texture->width = 0;
	texture->pixels = NULL;
}

bool Assets_LoadFile(Buffer *buffer, const char *filepath)
{
	FILE *file = fopen(filepath, "rb");
	if (!file)
	{
		Debug_Warn("Could not open file %s!", filepath);
		return false;
	}

	fseek(file, 0, SEEK_END);
	buffer->size = ftell(file);
	fseek(file, 0, SEEK_SET);

	buffer->data = (uint8_t*)malloc(buffer->size);
	if (!buffer->data)
	{
		Debug_Warn("Could not allocate buffer when loading file %s", filepath);
		return false;
	}

	if (fread(buffer->data, buffer->size, 1, file) != 1)
	{
		Debug_Warn("Could not read file %s!", filepath);
		return false;
	}

	return true;
}

bool Assets_LoadFont(TrueTypeFont *font, float height, const char *filepath)
{
	Buffer ttfBuffer;
	if (Assets_LoadFile(&ttfBuffer, filepath))
	{
		Bitmap2D *bitmap = &font->bitmap;

		bitmap->width = 512;
		bitmap->height = 512;
		bitmap->pixels = malloc(bitmap->width * bitmap->height * sizeof(*bitmap->pixels));

		font->pixelHeight = height;
		font->firstChar = 32;
		font->charCount = 96;

		if (!bitmap->pixels)
		{
			Debug_Warn("Could not allocate bitmap when loading font %s", filepath);
			return false;
		}

		stbtt_BakeFontBitmap(ttfBuffer.data, 0, font->pixelHeight, 
			bitmap->pixels, bitmap->width, bitmap->height, 
			font->firstChar, font->charCount, font->chars);

		Assets_FreeFile(&ttfBuffer);

		font->centerY = TrueTypeFont_CalculateCenterOffsetY(font);

		return true;
	}

	return false;
}

bool Assets_LoadFontFamily(FontFamily *family, float height,
	const char *normalPath,
	const char *boldPath,
	const char *italicPath,
	const char *boldItalicPath
)
{
	bool success = Assets_LoadFont(family->fonts + FontStyle_Normal, height, normalPath);
	success = Assets_LoadFont(family->fonts + FontStyle_Bold, height, boldPath) && success;
	success = Assets_LoadFont(family->fonts + FontStyle_Italic, height, italicPath) && success;
	success = Assets_LoadFont(family->fonts + FontStyle_BoldItalic, height, boldItalicPath) && success;
	return success;
}



