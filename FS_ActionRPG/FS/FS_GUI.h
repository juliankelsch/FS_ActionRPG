#ifndef __FS_GUI_H__
#define __FS_GUI_H__


#include "FS_Input.h"
#include "FS_RenderList2D.h"
#include "FS_Font.h"
#include "FS_Vector3.h"
#include "FS_Rectangle.h"

#include <stdarg.h>

typedef struct GUI GUI;


GUI *GUI_Create(Arena *arena, Keyboard *keyboard, Mouse *mouse, TimeInfo *timeInfo, Vector2 screen);
void GUI_Destroy(GUI *gui);

void GUI_BeginFrame(GUI *gui);
void GUI_EndFrame(GUI *gui);

typedef enum
{
	HAlignment_Left,
	HAlignment_Center,
	HAlignment_Right,
} HAlignment;

typedef enum
{
	VAlignment_Top,
	VAlignment_Center,
	VAlignment_Bot
} VAlignment;

typedef struct
{
	HAlignment horizontal;
	VAlignment vertical;
} Alignment;


typedef struct
{
	Rect rect;
	RectOffsets margin;
	RectOffsets border;
	RectOffsets padding;
} GUI_Box;

typedef enum
{
	OverflowMode_Ignore,
	OverflowMode_Wrap
} OverflowMode;


typedef enum
{
	ColorMode_Normal,
	ColorMode_Gradient
} ColorMode;

typedef enum
{
	TextCase_Normal,
	TextCase_Lower,
	TextCase_Upper
} TextCase;

typedef struct
{
	RectOffsets margin;
	RectOffsets outline;
	RectOffsets border;
	RectOffsets padding;
} GUI_BoxModel;

typedef struct
{
	Color margin;
	Color outline;
	Color border;
	Color padding;
	Color content;
} GUI_BoxModelColors;

Rect GUI_BoxModel_FillRect(GUI_BoxModel *model, Rect rect);

typedef struct
{
	// optional color or gradient
	ColorMode colorMode;
	Color color;

	Color gradientColors[Corner_Count];

	float lineSpacing;
	float characterSpacing;
	Alignment alignment;
	OverflowMode overflow;
	TextCase textCase;
	bool bold;
	bool italic;
} TextStyle;

RenderList2D *GUI_GetRenderList(GUI *gui);

// auto layout
void GUI_TextStyle_CreateDefault(TextStyle *style);

void GUI_Label(GUI *gui, const char *format, ...);
void GUI_Image(GUI *gui, Vector2 size, uint32_t textureID);
void GUI_EditFloat(GUI *gui, const char *label, float *value);
void GUI_EditBool(GUI *gui, const char *label, bool *value);
void GUI_EditVector3(GUI *gui, const char *label, Vector3 *value);
void GUI_EditVector2(GUI *gui, const char *label, Vector3 *value);
void GUI_EditEnum(GUI *gui, const char *label, const char **names, uint32_t *value);
void GUI_EditFlags(GUI *gui, const char *label, const char **names, uint32_t *value);
void GUI_EditText(GUI *gui, const char *label, uint32_t maxSize, char *value);

void RenderList2D_DrawImage(RenderList2D *renderList, Rect bounds, Vector2 imageSize, bool maintainAspect, Color tint, uint32_t textureID);
Vector2 RenderList2D_DrawText_Cursor(RenderList2D *renderList, FontFamily *family, Vector2 pos, Rect bounds, TextStyle *style, const char *text);
void RenderList2D_DrawText(RenderList2D *renderList, FontFamily *family, Rect bounds, TextStyle *style, const char *text);
void RenderList2D_DrawRect(RenderList2D *renderList, Rect rect, Color color);
void RenderList2D_DrawRectOutline(RenderList2D *renderList, Rect inner, Rect outer, Color color);
void RenderList2D_DrawBoxModel(RenderList2D *renderList, Rect contentRect, GUI_BoxModel *model, GUI_BoxModelColors *boxColors);

#endif // __FS_GUI_H__