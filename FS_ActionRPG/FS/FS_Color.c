#include "FS_Color.h"

Color Color_RGB(float red, float green, float blue)
{
	Color color = {
		red * 255,
		blue * 255,
		green * 255,
		255
	};
	return color;
}

Color Color_RGBA(float red, float green, float blue, float alpha)
{
	Color color = {
		red * 255,
		blue * 255,
		green * 255,
		alpha * 255
	};
	return color;

}