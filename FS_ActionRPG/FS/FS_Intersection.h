#ifndef __FS_INTERSECTION_H__
#define __FS_INTERSECTION_H__

#include <stdbool.h>

#include "FS_Vector2.h"


#include "FS_Mathf.h"

bool EdgeIntersects(Vector2 startA, Vector2 endA, Vector2 startB, Vector2 endB)
{
	float t0, t1;
	LineIntersection(startA, endA, startB, endB, &t0, &t1);
	return Mathf_IsInRange(t0, 0.0f, 1.0f)
		&& Mathf_IsInRange(t1, 0.0f, 1.0f);
}

// only works if the start and end points are not the same
void LineIntersection(Vector2 startA, Vector2 endA, Vector2 startB, Vector2 endB, float *t0, float *t1)
{
	float denom = (startA.x - endA.x) * (startB.y - endB.y) - (startA.y - endA.y) * (startB.x - endB.x);
	*t0 = (startA.x - startB.x) * (startB.y - endB.y) - (startA.y - startB.y) * (startB.x - endB.x)
		/ denom;
	*t1 = (startA.x - startB.x) * (startA.y - endA.y) - (startA.y - startB.y) * (startA.x - endA.x)
		/ denom;
}

bool PointInsidePolygon(Vector2 point, Vector2 *vertices, uint32_t vertexCount)
{
	Vector2 direction = { 0.623423f, 0.523132f };
	Vector2 p1 = Vector2_Add(point, direction);
	uint32_t intersections = 0;
	float t0 = Mathf_NegativeInfinity;
	float t1 = Mathf_NegativeInfinity;
	for (size_t i = 0; i < vertexCount; i++)
	{
		Vector2 e0 = vertices[i];
		Vector2 e1 = vertices[(i + 1) % vertexCount];
		LineIntersection(point, p1, e0, e1, &t0, &t1);
		intersections += t0 >= 0.0f && Mathf_IsInRange(t1, 0.0f, 1.0f);
	}
	return intersections % 2 == 1;
}

#endif // __FS_INTERSECTION_H__

