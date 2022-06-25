#include "FS_Vector2.h"

Vector2 Vector2_Create(float x, float y)
{
	Vector2 result = { x, y };
	return result;
}

Vector2 Vector2_Add(Vector2 a, Vector2 b)
{
	Vector2 result = {
		a.x + b.x,
		a.y + b.y
	};
	return result;
}

Vector2 Vector2_Subtract(Vector2 a, Vector2 b)
{
	Vector2 result = {
		a.x - b.x,
		a.y - b.y
	};
	return result;
}

Vector2 Vector2_Multiply(Vector2 a, Vector2 b)
{
	Vector2 result = {
		a.x * b.x,
		a.y * b.y
	};
	return result;
}

float Vector2_Dot(Vector2 a, Vector2 b)
{
	return a.x * b.x + a.y * b.y;
}