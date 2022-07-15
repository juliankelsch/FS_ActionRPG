#include "FS_Ray.h"


// Source (Moeller-Trumbore):
// https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
bool Ray3_IntersectsTriangle(vec3 origin, vec3 direction, vec3 v0, vec3 v1, vec3 v2, RayHitInfo *info)
{
	const float Epsilon = 0.000001f;

	vec3 edge1 = vec3_subtract(v1, v0);
	vec3 edge2 = vec3_subtract(v2, v0);

	vec3 h = vec3_cross(direction, edge2);
	float a = vec3_dot(edge1, h);
	if (a > -Epsilon && a < Epsilon)
	{
		return false;
	}
	float f = 1.0f / a;
	vec3 s = vec3_subtract(origin, v0);
	float u = f * vec3_dot(s, h);
	if (u < 0.0f || u > 1.0f)
	{
		return false;
	}
	vec3 q = vec3_cross(s, edge1);
	float v = f * vec3_dot(direction, q);
	if (v < 0.0f || u + v > 1.0f)
	{
		return false;
	}
	float t = f * vec3_dot(edge2, q);
	if (t > Epsilon)
	{
		info->point = vec3_add(origin, vec3_mulfiply_f(direction, t));
		info->distance = t;
		return true;
	}

	return false;
}

bool Ray3_GetClosestMeshIntersection(vec3 origin, vec3 direction, Mesh *mesh, RayHitInfo *info)
{
	RayHitInfo hitInfo = { 0 };
	float closest = Mathf_Infinity;

	bool hit = false;

	for (int i = 0; i < mesh->indexCount; i += 3)
	{
		vec3 v0 = mesh->vertices[mesh->indices[i]].position;
		vec3 v1 = mesh->vertices[mesh->indices[i + 1]].position;
		vec3 v2 = mesh->vertices[mesh->indices[i + 2]].position;

		if (Ray3_IntersectsTriangle(origin, direction, v0, v1, v2, &hitInfo))
		{
			hit = true;
			if (closest > hitInfo.distance)
			{
				*info = hitInfo;
				closest = hitInfo.distance;
			}
		}
	}

	return hit;
}
