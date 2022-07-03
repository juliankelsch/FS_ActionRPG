#include "FS_Rectangle.h"
#include "FS_Mathf.h"

Rect Rect_GetOffsetRect(Rect rect, RectOffsets offsets)
{
	Rect result =
	{ 
		rect.x - offsets.left,
		rect.y - offsets.top,
		rect.width + offsets.right + offsets.left,
		rect.height + offsets.top + offsets.bot,
	};
	return result;
}

bool Rect_IsPointInside(Rect rect, Vector2 point)
{
	return point.x >= rect.x
		&& point.x <= rect.x + rect.width
		&& point.y >= rect.y
		&& point.y <= rect.y + rect.height;
}

Rect Rect_GetInsetRect(Rect rect, RectOffsets offsets)
{
	Rect result =
	{ 
		rect.x + offsets.left,
		rect.y + offsets.top,
		rect.width - offsets.right - offsets.left,
		rect.height - offsets.top - offsets.bot,
	};
	return result;
}

Rect Rect_SplitVertical(Rect parent, Rect *top, Rect *bot, float percent)
{
	RectAnchors topAnchors = { 0.0f, 0.0f, 1.0f, percent};
	RectAnchors botAnchors = { 0.0f, percent, 1.0f, 1.0f};
	*top = Rect_GetAnchoredRect(parent, topAnchors);
	*bot = Rect_GetAnchoredRect(parent, botAnchors);
}

Rect Rect_SplitHorizontal(Rect parent, Rect *left, Rect *right, float percent)
{
	RectAnchors leftAnchors = { 0.0f, 0.0f, percent, 1.0f};
	RectAnchors rightAnchors = { percent, 0.0f, 1.0f, 1.0f};
	*left = Rect_GetAnchoredRect(parent, leftAnchors);
	*right = Rect_GetAnchoredRect(parent, rightAnchors);
}

Rect Rect_GetAnchoredRect(Rect parent, RectAnchors anchors)
{
	Rect result =
	{
		parent.x + parent.width * anchors.min.x,
		parent.y + parent.height * anchors.min.y,
		parent.width * (anchors.max.x - anchors.min.x),
		parent.height * (anchors.max.y - anchors.min.y)
	};
	return result;
}

Vector2 Rect_GetCorner(Rect rect, Corner corner)
{
	Vector2 result = { rect.x, rect.y };
	switch (corner)
	{
		case Corner_TopRight:
		{
			result.x += rect.width;
		} break;
		case Corner_BotLeft:
		{
			result.y += rect.height;
		} break;
		case Corner_BotRight:
		{
			result.x += rect.width;
			result.y += rect.height;
		} break;
	}
	return result;
}

void Rect_GetCorners(Rect rect, RectCorners out)
{
	for (size_t i = 0; i < Corner_Count; i++)
	{
		out[i] = Rect_GetCorner(rect, i);
	}
}