#include "FS_GUI.h"
#include "FS_Assets.h"
#include "FS_Macros.h"


struct GUI
{
	RenderList2D renderList;
	Arena *arena;
	Keyboard *keyboard;
	Mouse *mouse;
	TimeInfo *timeInfo;

	Vector2 screen;
	TrueTypeFont font;
	Vector2 cursor;
};

GUI *GUI_Create(Arena *arena, Keyboard *keyboard, Mouse *mouse, TimeInfo *timeInfo, Vector2 screen)
{
	GUI *gui = Arena_Push(arena, GUI);
	gui->screen = screen;
	gui->arena = arena;
	gui->keyboard = keyboard;
	gui->mouse = mouse;
	Assets_LoadFont(&gui->font, 25.0f, "resources/fonts/RobotoMono-Medium.ttf");
	gui->timeInfo = timeInfo;
	return gui;
}

void GUI_Destroy(GUI *gui)
{
	Assets_FreeFont(&gui->font);
}

void GUI_BeginFrame(GUI *gui)
{
	gui->cursor = (Vector2){0.0f, 0.0f};
}

void GUI_EndFrame(GUI *gui)
{

}

RenderList2D *GUI_GetRenderList(GUI *gui)
{
	return &gui->renderList;
}

void GUI_TextStyle_CreateDefault(TextStyle *style)
{
	style->colorMode = ColorMode_Normal;
	style->color = Color_White;
	for (size_t i = 0; i < ArrayCount(style->gradientColors); i++)
	{
		style->gradientColors[i] = Color_White;
	}
	style->alignment.horizontal = HAlignment_Left; 
	style->alignment.vertical = VAlignment_Top;
	style->textCase = TextCase_Normal;
	style->characterSpacing = 1.0f;
	style->lineSpacing = 1.0f;
	style->bold = false;
	style->italic = false;
}

void GUI_Label(GUI *gui, const char *format, ...)
{

}

void GUI_Image(GUI *gui, Vector2 size, uint32_t textureID)
{
	RenderList2D *list = GUI_GetRenderList(gui);
	RenderList2D_PushQuad(list, Vector2_Zero, size, Color_White, textureID);
}

void GUI_EditFloat(GUI *gui, const char *label, float *value)
{


}

void GUI_EditBool(GUI *gui, const char *label, bool *value);
void GUI_EditVector3(GUI *gui, const char *label, Vector3 *value);
void GUI_EditVector2(GUI *gui, const char *label, Vector3 *value);
void GUI_EditEnum(GUI *gui, const char *label, const char **names, uint32_t *value);
void GUI_EditFlags(GUI *gui, const char *label, const char **names, uint32_t *value);
void GUI_EditText(GUI *gui, const char *label, uint32_t maxSize, char *value);

/*
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, font->textureID);
    glBegin(GL_QUADS);

    while (*text) {
        if (*text >= font->firstChar && *text < (font->firstChar + font->charCount)) {
            stbtt_aligned_quad q;
            stbtt_GetBakedQuad(font->chars, font->bitmap.width, font->bitmap.height, *text - 32, &x, &y, &q, 1);//1=opengl & d3d10+,0=d3d9
            glTexCoord2f(q.s1, q.t0); glVertex2f(q.x1, q.y0);
            glTexCoord2f(q.s0, q.t0); glVertex2f(q.x0, q.y0);
            glTexCoord2f(q.s0, q.t1); glVertex2f(q.x0, q.y1);
            glTexCoord2f(q.s1, q.t1); glVertex2f(q.x1, q.y1);
        }
        ++text;
    }
    glEnd();
	*/

char ToUpper(char c)
{
	return c >= 'a' && c <= 'z' ? c - ('a' - 'A') : c;
}

char ToLower(char c)
{
	return c >= 'A' && c <= 'Z' ? c + ('a' - 'A') : c;
}

char ConvertCase(char character, TextCase textCase)
{
	if (textCase == TextCase_Upper)
	{
		character = ToUpper(character);
	}
	else if (textCase == TextCase_Lower)
	{
		character = ToLower(character);
	}
	return character;
}

float TrueTypeFont_GetLineWidth(TrueTypeFont *font, const char *text, float charSpacing, TextCase textCase)
{
	float width = 0.0f;
	while (*text && *text != '\n')
	{
		char character = ConvertCase(*text, textCase);

		if (TrueTypeFont_HasChar(font, character))
		{
			width += charSpacing * font->chars[character - font->firstChar].xadvance;
		}
		text++;
	}
	return width;
}

float GetNewLineX(HAlignment alignment, float left, float right, float lineWidth)
{
	switch (alignment)
	{
	case HAlignment_Left: return left;
	case HAlignment_Center: return (left + right) / 2.0f - lineWidth / 2.0f;
	case HAlignment_Right: return right - lineWidth;
	}
	return left;
}

float TrueTypeFont_GetTextHeight(TrueTypeFont *font, const char *text, float lineSpacing)
{
	float baselineOffset = font->pixelHeight * lineSpacing;
	float textHeight = baselineOffset;
	while (*text)
	{
		if (*text == '\n')
		{
			textHeight += baselineOffset;
		}
		text++;
	}
	return textHeight;
}

// Problem:
// We do a bunch of calculations at the beginning of this funcion
// before the while loop that we only want to do on the first call to this function
// when rendering a text block
// where we want words to be styled differently inside the same block.
// 
// though
// start and end functionfor text block
// 

// Text
// 
// # Multi-Style textblock
//
// TextStyle style;
// style.alignment = center;
// style.overflow = wrap;
// style.lineSpacing = 1.2;
// ...
//
// TextBlock *block = StartTextBlock(bounds, style);
// 
// AppendText(block, "Normal text");
// 
// SetFontStyle(block, italic);
// AppendText(block, "ItalicPage");
//
// SetFontStyle(block, bold);
// AppendText(block, "BoldPag");
// 
// EndTextBlock();

Vector2 RenderList2D_DrawText(RenderList2D *renderList, FontFamily *family, Vector2 pos, Rect bounds, TextStyle *style, const char *text)
{
	TrueTypeFont *font = family->fonts + ((style->bold) + (style->italic * 2));

	Color topLeft, topRight, botLeft, botRight;
	if (style->colorMode == ColorMode_Normal)
	{
		topLeft = style->color;
		topRight = style->color;
		botLeft = style->color;
		botRight = style->color;
	}
	else
	{
		topLeft = style->gradientColors[Corner_TopLeft];
		topRight = style->gradientColors[Corner_TopRight];
		botLeft = style->gradientColors[Corner_BotLeft];
		botRight = style->gradientColors[Corner_BotRight];
	}

	float baselineOffset = font->pixelHeight * style->lineSpacing;
	float top = bounds.y;
	float bot = bounds.y + bounds.height;
	float textHeight = TrueTypeFont_GetTextHeight(font, text, style->lineSpacing);

	switch (style->alignment.vertical)
	{
	case VAlignment_Top: pos.y += font->centerY; break;
	case VAlignment_Center: pos.y = (bot - top) / 2.0f - textHeight / 2.0f + font->centerY; break;
	case VAlignment_Bot: pos.y = bot - textHeight + font->centerY; break;
	}

	float left = bounds.x;
	float right = bounds.x + bounds.width;
	float lineWidth = TrueTypeFont_GetLineWidth(font, text, style->characterSpacing, style->textCase);

	pos.x = GetNewLineX(style->alignment.horizontal, left, right, lineWidth);

	CharacterQuad quad = { 0 };
	while (*text)
	{
		char character = ConvertCase(*text, style->textCase);

		if (character == '\n')
		{
			lineWidth = TrueTypeFont_GetLineWidth(font, text + 1, style->characterSpacing, style->textCase);
			pos.x = GetNewLineX(style->alignment.horizontal, left, right, lineWidth);
			pos.y += baselineOffset;
		}
		else if (TrueTypeFont_HasChar(font, character))
		{
			/*
			if (style->overflow == OverflowMode_Wrap)
			{
				// if horizontal left alignment
				if (*x > startX + maxWidth)
				{
					// next line
					*y += baselineOffset;
					*x = startX;
				}
			}
			*/

			TrueTypeFont_GetQuad(font, &pos.x, &pos.y, character, style->characterSpacing, &quad);
			Vertex2D vertices[] =
			{
				{{quad.x0, font->pixelHeight + quad.y0}, {quad.s0, quad.t0}, topLeft},
				{{quad.x1, font->pixelHeight + quad.y0}, {quad.s1, quad.t0}, topRight},
				{{quad.x0, font->pixelHeight + quad.y1}, {quad.s0, quad.t1}, botLeft},
				{{quad.x1, font->pixelHeight + quad.y1}, {quad.s1, quad.t1}, botRight},
			};

			uint32_t indices[] =
			{
				2, 1, 0,
				1, 2, 3
			};
			RenderList2D_PushMesh(renderList, ArrayCount(vertices), vertices, ArrayCount(indices), indices, font->textureID);
		}
		text++;
	}
	return pos;
}

void RenderList2D_DrawRect(RenderList2D *renderList, Rect rect, Color color)
{
	RenderList2D_PushQuad(renderList, (Vector2) {rect.x, rect.y}, (Vector2) {rect.width, rect.height}, color, 0);
}

