#ifndef __FS_TRANSFORM_H__
#define __FS_TRANSFORM_H__

#include "FS_Vector3.h"
#include "FS_Quaternion.h"

typedef struct
{
	vec3 position;
	Quaternion rotation;
	vec3 localScale;
} Transform;


void Transform_Create(Transform *transform);
void Transform_GetMatrix(Transform *transform, Matrix4 out);

#endif // __FS_TRANSFORM_H__