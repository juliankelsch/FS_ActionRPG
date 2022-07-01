#include "FS_Ray.h"


// Source (Moeller-Trumbore):
// https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
bool Ray3_IntersectsTriangle(Vector3 origin, Vector3 direction, Vector3 v0, Vector3 v1, Vector3 v2, RayHitInfo *info)
{
	const float Epsilon = 0.000001f;

	Vector3 edge1 = Vector3_Subtract(v1, v0);
	Vector3 edge2 = Vector3_Subtract(v2, v0);

	Vector3 h = Vector3_Cross(direction, edge2);
	float a = Vector3_Dot(edge1, h);
	if (a > -Epsilon && a < Epsilon)
	{
		return false;
	}
	float f = 1.0f / a;
	Vector3 s = Vector3_Subtract(origin, v0);
	float u = f * Vector3_Dot(s, h);
	if (u < 0.0f || u > 1.0f)
	{
		return false;
	}
	Vector3 q = Vector3_Cross(s, edge1);
	float v = f * Vector3_Dot(direction, q);
	if (v < 0.0f || u + v > 1.0f)
	{
		return false;
	}
	float t = f * Vector3_Dot(edge2, q);
	if (t > Epsilon)
	{
		info->point = Vector3_Add(origin, Vector3_Multiply_F(direction, t));
		info->distance = t;
		return true;
	}

	return false;
}

bool Ray3_GetClosestMeshIntersection(Vector3 origin, Vector3 direction, Mesh *mesh, RayHitInfo *info)
{
	RayHitInfo hitInfo = { 0 };
	float closest = Mathf_Infinity;

	bool hit = false;

	for (int i = 0; i < mesh->indexCount; i += 3)
	{
		Vector3 v0 = mesh->vertices[mesh->indices[i]].position;
		Vector3 v1 = mesh->vertices[mesh->indices[i + 1]].position;
		Vector3 v2 = mesh->vertices[mesh->indices[i + 2]].position;

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
