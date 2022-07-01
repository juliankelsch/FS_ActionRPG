#ifndef __FS_RAY_H__
#define __FS_RAY_H__

#include "FS_Mesh.h"
#include "FS_Vector3.h"
#include <stdbool.h>

typedef struct
{
	Vector3 origin;
	Vector3 direction;
} Ray3;

typedef struct
{
	Vector3 point;
	float distance;
} RayHitInfo;

bool Ray3_IntersectsTriangle(Vector3 origin, Vector3 direction, Vector3 v0, Vector3 v1, Vector3 v2, RayHitInfo *info);
bool Ray3_GetClosestMeshIntersection(Vector3 origin, Vector3 direction, Mesh *mesh, RayHitInfo *info);

#endif // __FS_RAY_H__