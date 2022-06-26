#ifndef __FS_MATHF_H__
#define __FS_MATHF_H__

#define Mathf_Pi 3.141592653f

float Mathf_Lerp(float a, float b, float t);
float Mathf_Sqrt(float x);
float Mathf_Clamp(float x, float low, float high);
float Mathf_Clamp01(float x);
float Mathf_MapToRange(float x, float fromLow, float fromHigh, float toLow, float toHigh);
float Mathf_Radians(float degrees);
float Mathf_Degrees(float radians);
float Mathf_Abs(float x);

float Mathf_Sin(float x);
float Mathf_Cos(float x);
float Mathf_Tan(float x);
float Mathf_Atan2(float y, float x);
float Mathf_Atan(float x);
float Mathf_Acos(float x);
float Mathf_Asin(float x);

#endif // __FS_MATHF_H__