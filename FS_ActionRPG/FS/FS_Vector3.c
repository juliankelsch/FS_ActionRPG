#include "FS_Vector3.h"

vec3 vec3_create(float x, float y, float z)
{
	vec3 result = { x, y, z };
	return result;
}

vec3 vec3_add(vec3 a, vec3 b)
{
	vec3 result = {
		a.x + b.x, 
		a.y + b.y,
		a.z + b.z
	};
	return result;
}

vec3 vec3_subtract(vec3 a, vec3 b)
{
	vec3 result = {
		a.x - b.x, 
		a.y - b.y,
		a.z - b.z
	};
	return result;
}

vec3 vec3_multiply(vec3 a, vec3 b)
{
	vec3 result = {
		a.x * b.x, 
		a.y * b.y,
		a.z * b.z
	};
	return result;
}

vec3 vec3_mulfiply_f(vec3 v, float s)
{
	vec3 result = {
		v.x * s,
		v.y * s,
		v.z * s
	};
	return result;
}

vec3 vec3_cross(vec3 a, vec3 b)
{
	vec3 result = {
		a.y * b.z - b.y * a.z,
		a.z * b.x - b.z * a.x,
		a.x * b.y - b.x * a.y
	};
	return result;
}

float vec3_dot(vec3 a, vec3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float vec3_length(vec3 v)
{
	return Mathf_Sqrt(vec3_dot(v, v));
}

vec3 vec3_normalized(vec3 v)
{
	return vec3_mulfiply_f(v, 1.0f / vec3_length(v));
}

vec3 vec3_normalized_safe(vec3 v)
{
	float mag = vec3_length(v);
	if (mag != 0.0f)
	{
		return vec3_mulfiply_f(v, 1.0f / mag);
	}
	return v;
}

vec3 vec3_direction(vec3 a, vec3 b)
{
	return vec3_normalized_safe(vec3_subtract(b, a));
}

float vec3_distance(vec3 a, vec3 b)
{
	return vec3_length(vec3_subtract(a, b));
}

vec3 vec3_lerp(vec3 a, vec3 b, float t)
{
	vec3 res = {
		Mathf_Lerp(a.x, b.x, t),
		Mathf_Lerp(a.y, b.y, t),
		Mathf_Lerp(a.z, b.z, t),
	};
	return res;
}

vec3 vec3_from_vec4(vec4 v)
{
	vec3 res = {
		v.x / v.w,
		v.y / v.w,
		v.z / v.w,
	};
	return res;
}
