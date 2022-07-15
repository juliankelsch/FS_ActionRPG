#ifndef __FS_RAY_H__
#define __FS_RAY_H__

#include "FS_Mesh.h"
#include "FS_Vector3.h"
#include <stdbool.h>

typedef struct
{
	vec3 origin;
	vec3 direction;
} Ray3;

typedef struct
{
	vec3 point;
	float distance;
} RayHitInfo;

bool Ray3_IntersectsTriangle(vec3 origin, vec3 direction, vec3 v0, vec3 v1, vec3 v2, RayHitInfo *info);
bool Ray3_GetClosestMeshIntersection(vec3 origin, vec3 direction, Mesh *mesh, RayHitInfo *info);

#endif // __FS_RAY_H__