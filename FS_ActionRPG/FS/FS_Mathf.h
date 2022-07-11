#ifndef __FS_MATHF_H__
#define __FS_MATHF_H__

#include <float.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum
{
	Ease_Linear,
	Ease_QuadIn,
	Ease_QuadOut,
} Ease;

typedef enum
{
	Axis_X,
	Axis_Y,
	Axis_Z,
} Axis;

typedef enum
{
	Direction_Up,
	Direction_Right,
	Direction_Down,
	Direction_Left
} Direction;

#define Mathf_Pi 3.141592653f
#define Mathf_Infinity FLT_MAX
#define Mathf_NegativeInfinity FLT_MIN

float Mathf_Lerp(float a, float b, float t);
float Mathf_Ease(float x, Ease ease);
float Mathf_Sqrt(float x);
float Mathf_Clamp(float x, float low, float high);
float Mathf_Clamp01(float x);
float Mathf_MapToRange(float x, float fromLow, float fromHigh, float toLow, float toHigh);
float Mathf_Radians(float degrees);
float Mathf_Degrees(float radians);
float Mathf_Abs(float x);
float Mathf_Min(float a, float b);
float Mathf_Max(float a, float b);

// inclusive for low AND high
bool Mathf_IsInRange(float value, float low, float high);

int32_t Math_Min(int32_t a, int32_t b);
int32_t Math_Max(int32_t a, int32_t b);
int32_t Math_Clamp(int32_t x, int32_t low, int32_t high);

float Mathf_Random01();

float Mathf_Sin(float x);
float Mathf_Cos(float x);
float Mathf_Tan(float x);
float Mathf_Atan2(float y, float x);
float Mathf_Atan(float x);
float Mathf_Acos(float x);
float Mathf_Asin(float x);


#endif // __FS_MATHF_H__