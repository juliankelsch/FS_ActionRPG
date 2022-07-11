#ifndef __FS_INTERSECTION_H__
#define __FS_INTERSECTION_H__

#include <stdbool.h>

#include "FS_Vector2.h"
#include "FS_Mathf.h"

// geometry
bool Geometry_EdgesIntersect(Vector2 startA, Vector2 endA, Vector2 startB, Vector2 endB)
{
	float t0, t1;
	return Geometry_LinesIntersect(startA, endA, startB, endB, &t0, &t1)
		&& Mathf_IsInRange(t0, 0.0f, 1.0f)
		&& Mathf_IsInRange(t1, 0.0f, 1.0f);
}

bool Geometry_LinesIntersect(Vector2 startA, Vector2 endA, Vector2 startB, Vector2 endB, float *t0, float *t1)
{
	// if denom == 0
	//		lines are parallel 
	//		OR
	//		any of the lines have the same start and end point thus not forming a line
	float denom = (startA.x - endA.x) * (startB.y - endB.y) - (startA.y - endA.y) * (startB.x - endB.x);
	if (denom != 0.0f)
	{
		*t0 = (startA.x - startB.x) * (startB.y - endB.y) - (startA.y - startB.y) * (startB.x - endB.x)
			/ denom;
		*t1 = (startA.x - startB.x) * (startA.y - endA.y) - (startA.y - startB.y) * (startA.x - endA.x)
			/ denom;
		return true;
	}
	return false;
}

bool Geometry_IsPointInsidePolygon(Vector2 point, Vector2 *vertices, uint32_t vertexCount)
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
		bool edgeIntersects = Geometry_LinesIntersect(point, p1, e0, e1, &t0, &t1)
			&& t0 >= 0.0f
			&& Mathf_IsInRange(t1, 0.0f, 1.0f);
		intersections += edgeIntersects;
	}
	return intersections % 2 == 1;
}


#endif // __FS_INTERSECTION_H__

