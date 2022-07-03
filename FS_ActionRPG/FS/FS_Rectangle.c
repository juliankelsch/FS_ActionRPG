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
	*top = Rect_AnchorToParent(parent, topAnchors);
	*bot = Rect_AnchorToParent(parent, botAnchors);
}

Rect Rect_SplitHorizontal(Rect parent, Rect *left, Rect *right, float percent)
{
	RectAnchors leftAnchors = { 0.0f, 0.0f, percent, 1.0f};
	RectAnchors rightAnchors = { percent, 0.0f, 1.0f, 1.0f};
	*left = Rect_AnchorToParent(parent, leftAnchors);
	*right = Rect_AnchorToParent(parent, rightAnchors);
}

RectAnchors Rect_GetAlignedAnchors(RectAnchors anchors, Alignment alignment)
{
	RectAnchors result = Rect_GetAlignedAnchorsHorizontal(anchors, alignment.horizontal);
	result = Rect_GetAlignedAnchorsVertical(result, alignment.vertical);
	return result;
}

RectAnchors Rect_GetAlignedAnchorsHorizontal(RectAnchors anchors, HAlignment alignment)
{
	RectAnchors result = anchors;
	float anchorsWidth = anchors.max.x - anchors.min.x;

	switch (alignment)
	{
	case HAlignment_Left: 
	{
		result.min.x = 0.0f;
		result.max.x = anchorsWidth;
	} break;
	case HAlignment_Center:
	{
		result.min.x = 0.5f - anchorsWidth / 2.0f;
		result.max.x = 0.5f + anchorsWidth / 2.0f;
	} break;
	case HAlignment_Right: 
	{
		result.min.x = 1.0f - anchorsWidth;
		result.max.x = 1.0f;
	} break;
	default:
		break;
	}
	return result;

}

RectAnchors Rect_GetAlignedAnchorsVertical(RectAnchors anchors, VAlignment alignment)
{
	RectAnchors result = anchors;
	float anchorsHeight = anchors.max.y - anchors.min.y;

	switch (alignment)
	{
	case HAlignment_Left: 
	{
		result.min.y = 0.0f;
		result.max.y = anchorsHeight;
	} break;
	case HAlignment_Center:
	{
		result.min.y = 0.5f - anchorsHeight / 2.0f;
		result.max.y = 0.5f + anchorsHeight / 2.0f;
	} break;
	case HAlignment_Right: 
	{
		result.min.y = 1.0f - anchorsHeight;
		result.max.y = 1.0f;
	} break;
	default:
		break;
	}
	return result;
}

Rect Rect_AnchorToParent(Rect parent, RectAnchors anchors)
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

Rect Rect_GetAlignedRect(Rect parent, Rect child, Alignment alignment)
{
	Rect result = Rect_GetAlignedRectHorizontal(parent, child, alignment.horizontal);
	result = Rect_GetAlignedRectVertical(parent, result, alignment.vertical);
	return result;
}

Rect Rect_GetAlignedRectHorizontal(Rect parent, Rect child, HAlignment alignment)
{
	Rect result = child;
	switch (alignment)
	{
	case HAlignment_Left: 
	{
		result.x = parent.x;
	} break;
	case HAlignment_Center:
	{
		result.x = parent.x + parent.width / 2.0f - child.width / 2.0f;
	} break;
	case HAlignment_Right: 
	{
		result.x = parent.x + parent.width - child.width;
	} break;
	default:
		break;
	}
	return result;
}

Rect Rect_GetAlignedRectVertical(Rect parent, Rect child, VAlignment alignment)
{
	Rect result = child;
	switch (alignment)
	{
	case VAlignment_Top: 
	{
		result.y = parent.y;
	} break;
	case VAlignment_Center:
	{
		result.y = parent.y + parent.height / 2.0f - child.height / 2.0f;
	} break;
	case VAlignment_Bot: 
	{
		result.y = parent.y + parent.height - child.height;
	} break;
	default:
		break;
	}
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