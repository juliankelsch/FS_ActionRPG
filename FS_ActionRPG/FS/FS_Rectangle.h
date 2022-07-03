#ifndef __FS_RECTANGLE_H__
#define __FS_RECTANGLE_H__

#include <stdint.h>
#include <stdbool.h>

#include "FS_Vector2.h"

typedef enum
{
	Corner_TopLeft,
	Corner_TopRight,
	Corner_BotLeft,
	Corner_BotRight,

	Corner_Count
} Corner;

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

typedef union
{
	struct
	{
		float x, y, width, height;
	};
	struct
	{
		Vector2 pos, size;
	};
} Rect;

typedef union
{
	struct
	{
		int32_t x, y, width, height;
	};
	struct
	{
		Vector2Int pos, size;
	};
} RectInt;

typedef Vector2 RectCorners[Corner_Count];

typedef struct
{
	float top, left, bot, right;
} RectOffsets;

typedef struct
{
	Vector2 min;
	Vector2 max;
} RectAnchors;

Rect Rect_GetOffsetRect(Rect rect, RectOffsets offsets);
Rect Rect_GetInsetRect(Rect rect, RectOffsets offsets);
Rect Rect_AnchorToParent(Rect parent, RectAnchors anchors);
RectAnchors Rect_GetAlignedAnchors(RectAnchors anchors, Alignment alignment);
RectAnchors Rect_GetAlignedAnchorsHorizontal(RectAnchors anchors, HAlignment alignment);
RectAnchors Rect_GetAlignedAnchorsVertical(RectAnchors anchors, VAlignment alignment);
Rect Rect_GetAlignedRect(Rect parent, Rect child, Alignment alignment);
Rect Rect_GetAlignedRectHorizontal(Rect parent, Rect child, HAlignment alignment);
Rect Rect_GetAlignedRectVertical(Rect parent, Rect child, VAlignment alignment);

bool Rect_IsPointInside(Rect rect, Vector2 point);

Rect Rect_SplitVertical(Rect parent, Rect *top, Rect *bot, float percent);
Rect Rect_SplitHorizontal(Rect parent, Rect *left, Rect *right, float percent);
Vector2 Rect_GetCorner(Rect rect, Corner corner);
void Rect_GetCorners(Rect rect, RectCorners out);

#endif // __FS_RECTANGLE_H__