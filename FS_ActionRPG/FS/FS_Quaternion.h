#ifndef __FS_QUATERNION_H__
#define __FS_QUATERNION_H__

#include "FS_Vector3.h"
#include "FS_Matrix4.h"

typedef struct
{
	float s;
	vec3 v;
} Quaternion;

Quaternion Quaternion_Identity();
Quaternion Quaternion_AxisAngle(float angle, vec3 axis);

Quaternion Quaternion_Inverse(Quaternion quat);
Quaternion Quaternion_Conjugate(Quaternion quat);
Quaternion Quaternion_Normalize(Quaternion quat);
Quaternion Quaternion_FromMatrix(Matrix4 m);
void Quaternion_ToMatrix(Matrix4 matrix, Quaternion quat);
Quaternion Quaternion_Slerp(Quaternion a, Quaternion b, float t);
float Quaternion_Dot(Quaternion a, Quaternion b);
float Quaternion_Length(Quaternion quat);
vec3 Quaternion_Rotate(vec3 point, Quaternion quat);

Quaternion Quaternion_Add(Quaternion a, Quaternion b);
Quaternion Quaternion_Subtract(Quaternion a, Quaternion b);
Quaternion Quaternion_Multiply(Quaternion a, Quaternion b);
Quaternion Quaternion_Multiply_F(Quaternion quat, float scalar);

#endif // __FS_QUATERNION_H__
