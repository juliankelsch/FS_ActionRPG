#ifndef __FS_MESH_H__
#define __FS_MESH_H__

#include "FS_Vector2.h"
#include "FS_Vector3.h"
#include "FS_Matrix4.h"
#include "FS_Color.h"
#include "FS_Arena.h"

typedef struct
{
	vec3 position;
	vec3 normal;
	vec2 texCoords;
	Color color;
} Vertex;

typedef struct
{
	uint32_t vertexCount;
	uint32_t indexCount;

	Vertex *vertices;
	uint32_t *indices;
} Mesh;

Mesh Mesh_CreateQuad(Arena *arena);
Mesh Mesh_CreatePlane(Arena *arena, vec3 baseA, vec3 baseB, float size, uint32_t subDivisions);
Mesh Mesh_CreateCube(Arena *arena);
Mesh Mesh_CreateSphere(Arena *arena, uint32_t horizontalSlices, uint32_t verticalSlices);
Mesh Mesh_CreateCircle(Arena *arena, float radius, uint32_t segments);
Mesh Mesh_CreateCone(Arena *arena, float height, float radius, uint32_t segments);
Mesh Mesh_CreateCylinder(Arena *arena, float height, float radius, uint32_t segments);
/*
Mesh Mesh_CreateCapsule(Arena *arena);
Mesh Mesh_CreateCone(Arena *arena);
*/

void Mesh_ApplyTransform(Mesh *mesh, Matrix4 transform);
Mesh Mesh_Combine(Arena *arena, Mesh *meshA, Mesh *meshB);

#endif // __FS_MESH_H__