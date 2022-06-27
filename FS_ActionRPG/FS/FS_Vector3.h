#ifndef __FS_VECTOR3_H__
#define __FS_VECTOR3_H__

#include "FS_Vector4.h"
#include "FS_Mathf.h"

typedef struct
{
	float x, y, z;
} Vector3;

#define Vector3_Zero	(Vector3){0.0f, 0.0f, 0.0f}
#define Vector3_One		(Vector3){1.0f, 1.0f, 1.0f}

#define Vector3_X (Vector3){1.0f, 0.0f, 0.0f}
#define Vector3_Y (Vector3){0.0f, 1.0f, 0.0f}
#define Vector3_Z (Vector3){0.0f, 0.0f, 1.0f}

#define Vector3_Right	(Vector3){ 1.0f,  0.0f,  0.0f}
#define Vector3_Left	(Vector3){-1.0f,  0.0f,  0.0f}
#define Vector3_Up		(Vector3){ 0.0f,  1.0f,  0.0f}
#define Vector3_Down	(Vector3){ 0.0f, -1.0f,  0.0f}
#define Vector3_Forward (Vector3){ 0.0f,  0.0f,  1.0f}
#define Vector3_Back	(Vector3){ 0.0f,  0.0f, -1.0f}

Vector3 Vector3_Create(float x, float y, float z);
Vector3 Vector3_Add(Vector3 a, Vector3 b);
Vector3 Vector3_Subtract(Vector3 a, Vector3 b);
Vector3 Vector3_Multiply(Vector3 a, Vector3 b);
Vector3 Vector3_Multiply_F(Vector3 v, float s);
Vector3 Vector3_Cross(Vector3 a, Vector3 b);
float Vector3_Dot(Vector3 a, Vector3 b);
float Vector3_Length(Vector3 v);
Vector3 Vector3_Normalized(Vector3 v);
Vector3 Vector3_NormalizedSafe(Vector3 v);
Vector3 Vector3_Direction(Vector3 from, Vector3 to);
float Vector3_Distance(Vector3 a, Vector3 b);
Vector3 Vector3_Lerp(Vector3 a, Vector3 b, float t);
Vector3 Vector3_From_V4(Vector4 v);

#endif // __FS_VECTOR3_H__