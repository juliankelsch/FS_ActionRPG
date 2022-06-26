#ifndef __FS_MESH_H__
#define __FS_MESH_H__

#include "FS_Vector2.h"
#include "FS_Vector3.h"
#include "FS_Matrix4.h"
#include "FS_Color.h"
#include "FS_Arena.h"

typedef struct
{
	Vector3 position;
	Vector3 normal;
	Vector2 texCoords;
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
Mesh Mesh_CreatePlane(Arena *arena, Vector3 baseA, Vector3 baseB, uint32_t subDivisions);
Mesh Mesh_CreateCube(Arena *arena);
void Mesh_ApplyTransform(Mesh *mesh, Matrix4 transform);
Mesh Mesh_Combine(Arena *arena, Mesh *meshA, Mesh *meshB);

#endif // __FS_MESH_H__