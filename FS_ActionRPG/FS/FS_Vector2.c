#include "FS_Vector2.h"

#include "FS_Mathf.h"
#include "FS_Debug.h"

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

float Vector2_Cross(Vector2 a, Vector2 b)
{
	return a.x * b.y - a.y * b.x;
}

float Vector2_Length(Vector2 v)
{
	return Mathf_Sqrt(Vector2_Dot(v, v));
}

float Vector2_Distance(Vector2 a, Vector2 b)
{
	return Vector2_Length(Vector2_Subtract(a, b));
}

Vector2 Vector2_Direction(Vector2 from, Vector2 to)
{
	return Vector2_NormalizedSafe(Vector2_Subtract(to, from));
}

Vector2 Vector2_Multiply_F(Vector2 v, float s)
{
	Vector2 result = {
		v.x * s,
		v.y * s
	};
	return result;

}

Vector2 Vector2_Normalized(Vector2 v)
{
	return Vector2_Multiply_F(v, 1.0f / Vector2_Length(v));
}

Vector2 Vector2_NormalizedSafe(Vector2 v)
{
	float mag = Vector2_Length(v);
	if (mag != 0.0f)
	{
		return Vector2_Multiply_F(v, 1.0f / mag);
	}

	return v;
}

Vector2 Vector2_GetNormal(Vector2 v)
{
	return Vector2_Normalized((Vector2){ -v.y, v.x });
}