#include "FS_Vector3.h"

Vector3 Vector3_Create(float x, float y, float z)
{
	Vector3 result = { x, y, z };
	return result;
}

Vector3 Vector3_Add(Vector3 a, Vector3 b)
{
	Vector3 result = {
		a.x + b.x, 
		a.y + b.y,
		a.z + b.z
	};
	return result;
}

Vector3 Vector3_Subtract(Vector3 a, Vector3 b)
{
	Vector3 result = {
		a.x - b.x, 
		a.y - b.y,
		a.z - b.z
	};
	return result;
}

Vector3 Vector3_Multiply(Vector3 a, Vector3 b)
{
	Vector3 result = {
		a.x * b.x, 
		a.y * b.y,
		a.z * b.z
	};
	return result;
}

Vector3 Vector3_Multiply_F(Vector3 v, float s)
{
	Vector3 result = {
		v.x * s,
		v.y * s,
		v.z * s
	};
	return result;
}

Vector3 Vector3_Cross(Vector3 a, Vector3 b)
{
	Vector3 result = {
		a.y * b.z - b.y * a.z,
		a.z * b.x - b.z * a.x,
		a.x * b.y - b.x * a.y
	};
	return result;
}

float Vector3_Dot(Vector3 a, Vector3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float Vector3_Length(Vector3 v)
{
	return Mathf_Sqrt(Vector3_Dot(v, v));
}

Vector3 Vector3_Normalized(Vector3 v)
{
	return Vector3_Multiply_F(v, 1.0f / Vector3_Length(v));
}

Vector3 Vector3_NormalizedSafe(Vector3 v)
{
	float mag = Vector3_Length(v);
	if (mag != 0.0f)
	{
		return Vector3_Multiply_F(v, 1.0f / mag);
	}
	return v;
}

Vector3 Vector3_Direction(Vector3 a, Vector3 b)
{
	return Vector3_NormalizedSafe(Vector3_Subtract(b, a));
}

float Vector3_Distance(Vector3 a, Vector3 b)
{
	return Vector3_Length(Vector3_Subtract(a, b));
}

Vector3 Vector3_Lerp(Vector3 a, Vector3 b, float t)
{
	Vector3 res = {
		Mathf_Lerp(a.x, b.x, t),
		Mathf_Lerp(a.y, b.y, t),
		Mathf_Lerp(a.z, b.z, t),
	};
	return res;
}

Vector3 Vector3_From_V4(Vector4 v)
{
	Vector3 res = {
		v.x / v.w,
		v.y / v.w,
		v.z / v.w,
	};
	return res;
}
