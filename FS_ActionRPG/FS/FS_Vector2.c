#include "FS_Vector2.h"

#include "FS_Mathf.h"
#include "FS_Debug.h"

vec2 vec2_create(float x, float y)
{
	vec2 result = { x, y };
	return result;
}

vec2 vec2_add(vec2 a, vec2 b)
{
	vec2 result = {
		a.x + b.x,
		a.y + b.y
	};
	return result;
}

vec2 vec2_subtract(vec2 a, vec2 b)
{
	vec2 result = {
		a.x - b.x,
		a.y - b.y
	};
	return result;
}

vec2 vec2_multiply(vec2 a, vec2 b)
{
	vec2 result = {
		a.x * b.x,
		a.y * b.y
	};
	return result;
}

float vec2_dot(vec2 a, vec2 b)
{
	return a.x * b.x + a.y * b.y;
}

float vec2_cross(vec2 a, vec2 b)
{
	return a.x * b.y - a.y * b.x;
}

float vec2_length(vec2 v)
{
	return sqrtf(vec2_dot(v, v));
}

float vec2_distance(vec2 a, vec2 b)
{
	return vec2_length(vec2_subtract(a, b));
}

vec2 vec2_direction(vec2 from, vec2 to)
{
	return vec2_normalized_safe(vec2_subtract(to, from));
}

vec2 vec2_multiply_f(vec2 v, float s)
{
	vec2 result = {
		v.x * s,
		v.y * s
	};
	return result;

}

vec2 vec2_normalized(vec2 v)
{
	return vec2_multiply_f(v, 1.0f / vec2_length(v));
}

vec2 vec2_normalized_safe(vec2 v)
{
	float mag = vec2_length(v);
	if (mag != 0.0f)
	{
		return vec2_multiply_f(v, 1.0f / mag);
	}

	return v;
}

vec2 vec2_nomal(vec2 v)
{
	return vec2_normalized((vec2){ -v.y, v.x });
}