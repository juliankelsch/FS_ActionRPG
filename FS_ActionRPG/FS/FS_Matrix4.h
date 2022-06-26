#ifndef __FS_MATRIX4_H__
#define __FS_MATRIX4_H__

#include <stdbool.h>

#include "FS_Vector3.h"
#include "FS_Vector4.h"

typedef float Matrix4Row[4];
typedef Matrix4Row Matrix4[4];
void Matrix4_Create(Matrix4 m, float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33);
void Matrix4_Identity(Matrix4 m);
void Matrix4_Zero(Matrix4 m);
void Matrix4_Copy(Matrix4 res, Matrix4 m);
void Matrix4_Transpose(Matrix4 res, Matrix4 m);
bool Matrix4_Inverse(Matrix4 res, Matrix4 m);

void Matrix4_Add(Matrix4 res, Matrix4 a, Matrix4 b);
void Matrix4_Subtract(Matrix4 res, Matrix4 a, Matrix4 b);
void Matrix4_Multiply_M4(Matrix4 res, Matrix4 a, Matrix4 b);
void Matrix4_Multiply_F(Matrix4 res, Matrix4 m, float s);

Vector4 Matrix4_Multiply_V4(Matrix4 m, Vector4 p);

Vector3 Matrix4_Multiply_Point3(Matrix4 m, Vector3 p);
Vector3 Matrix4_Multiply_Direction3(Matrix4 m, Vector3 d);

void Matrix4_LookAt(Matrix4 m, Vector3 eye, Vector3 target);
void Matrix4_Orthographic(Matrix4 m, float l, float r, float t, float b, float n, float f);
void Matrix4_Frustum(Matrix4 m, float l, float r, float t, float b, float n, float f);
void Matrix4_Perspective(Matrix4 m, float fovy, float aspect, float near, float far);

#endif // __FS_MATRIX4_H__