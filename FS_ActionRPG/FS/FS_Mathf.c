#include "FS_Mathf.h"

#include <math.h>
#include <stdlib.h>

float Mathf_Lerp(float a, float b, float t)
{
	return (1.0f - t) * a + t * b;
}

float Mathf_Ease(float x, Ease ease)
{
	switch (ease)
	{
	case Ease_QuadIn:
		return x * x;
	case Ease_QuadOut:
		return 1.0f - (1.0f - x) * (1.0f - x);
	default:
		return x;
		break;
	}
}

float Mathf_Sqrt(float x)
{
	return sqrtf(x);
}

float Mathf_Clamp(float x, float low, float high)
{
	return x < low ? low : (x > high ? high : x);
}

float Mathf_Clamp01(float x)
{
	return Mathf_Clamp(x, 0.0f, 1.0f);
}

float Mathf_MapToRange(float x, float fromLow, float fromHigh, float toLow, float toHigh)
{
	float percent = (x - fromLow) / (fromHigh - fromLow);
	return Mathf_Lerp(toLow, toHigh, percent);
}

float Mathf_Radians(float degrees)
{
	return (degrees / 180.0f) * Mathf_Pi;
}

float Mathf_Degrees(float radians)
{
	return (radians / Mathf_Pi) * 180.0f;
}

float Mathf_Abs(float x)
{
	return fabsf(x);
}

float Mathf_Random01(float x)
{
	return (float)rand() / RAND_MAX;
}

float Mathf_Sin(float x)
{
	return sinf(x);
}

float Mathf_Cos(float x)
{
	return cosf(x);
}

float Mathf_Tan(float x)
{
	return tanf(x);
}

float Mathf_Atan2(float y, float x)
{
	return atan2f(y, x);
}

float Mathf_Atan(float x)
{
	return atanf(x);
}

float Mathf_Acos(float x)
{
	return acosf(x);
}

float Mathf_Asin(float x)
{
	return asinf(x);
}
