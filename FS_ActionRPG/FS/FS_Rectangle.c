#include "FS_Rectangle.h"

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