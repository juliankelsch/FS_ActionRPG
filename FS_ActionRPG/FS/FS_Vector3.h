#ifndef __FS_VECTOR3_H__
#define __FS_VECTOR3_H__

typedef struct
{
	float x, y, z;
} Vector3;

Vector3 Vector3_Add(Vector3 a, Vector3 b);

#endif // __FS_VECTOR3_H__