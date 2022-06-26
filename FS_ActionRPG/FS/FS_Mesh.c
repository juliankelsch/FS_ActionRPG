#include "FS_Mesh.h"
#include "FS_Macros.h"

#include <string.h>


Mesh Mesh_CreateQuad(Arena *arena)
{
	Mesh quad = { 0 };

	quad.vertexCount = 4;
	quad.indexCount = 6;
	quad.vertices = Arena_PushArray(arena, quad.vertexCount, Vertex);
	quad.indices =	Arena_PushArray(arena, quad.indexCount, uint32_t);

	Vector3 normal = { 0, 0, 1 };
	Color color = { 255, 255, 255, 255 };

	quad.vertices[0] = (Vertex){ {-0.5f, 0.5f}, normal, {0.0f, 1.0f}, color };
	quad.vertices[1] = (Vertex){ {0.5f, 0.5f}, normal, {1.0f, 1.0f}, color };
	quad.vertices[2] = (Vertex){ {-0.5f, -0.5f}, normal, { 0.0f, 0.0f }, color};
	quad.vertices[3] = (Vertex){ {0.5f, -0.5f}, normal, { 1.0f, 0.0f }, color};

	quad.indices[0] = 0;
	quad.indices[1] = 2;
	quad.indices[2] = 1;

	quad.indices[3] = 1;
	quad.indices[4] = 2;
	quad.indices[5] = 3;

	return quad;
}

Mesh Mesh_CreatePlane(Arena *arena, Vector3 baseA, Vector3 baseB, uint32_t subDivisions)
{
	Mesh mesh = { 0 };

	const int edgeCount = subDivisions + 2;
	const int quadCount = subDivisions + 1;

	mesh.vertexCount = edgeCount * edgeCount;
	mesh.indexCount = quadCount * quadCount * 6;
	mesh.vertices = Arena_PushArray(arena, mesh.vertexCount, Vertex);
	mesh.indices =	Arena_PushArray(arena, mesh.indexCount, uint32_t);

	Vector3 normal = { 0, 1, 0 };
	Color color = { 255, 255, 255, 255 };
	for (size_t i = 0; i < edgeCount; i++)
	{
		for (size_t j = 0; j < edgeCount; j++)
		{
			Vertex *vertex = mesh.vertices + i * edgeCount + j;
			float a = (float)j / (edgeCount - 1);
			float b = (float)i / (edgeCount - 1);

			vertex->position.x = ((baseA.x * a + baseB.x * b) - (0.5f * (baseA.x + baseB.x)));
			vertex->position.y = ((baseA.y * a + baseB.y * b) - (0.5f * (baseA.y + baseB.y)));
			vertex->position.z = ((baseA.z * a + baseB.z * b) - (0.5f * (baseA.z + baseB.z)));

			vertex->normal = normal;
			vertex->color = color;
			vertex->texCoords = (Vector2){ j / (edgeCount - 1), i / (edgeCount - 1) };
		}
	}

	uint32_t *index = mesh.indices;
	for (size_t i = 0; i < quadCount; i++)
	{
		for (size_t j = 0; j < quadCount; j++)
		{
			size_t topLeft = i * edgeCount + j;
			size_t botLeft = (i + 1) * edgeCount + j;
			size_t topRight = topLeft + 1;
			size_t botRight = botLeft + 1;

			*index++ = topLeft;
			*index++ = botLeft;
			*index++ = topRight;

			*index++ = topRight;
			*index++ = botLeft;
			*index++ = botRight;
		}
	}
	return mesh;
}

Mesh Mesh_CreateCube(Arena *arena)
{
	Mesh mesh = { 0 };

	Vector3 normal = { 0, 1, 0 };
	Color color = { 255, 255, 255, 255 };

	Vertex vertices[] =
	{
		// back
		{ {-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}, color },
		{ {0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}, color },
		{ {-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, color },
		{ {0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}, color },

		// front
		{ {0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}, color },
		{ {-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, color },
		{ {0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, color },
		{ {-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}, color },

		// right
		{ {0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}, color },
		{ {0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, color },
		{ {0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, color },
		{ {0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}, color },

		// left
		{ {-0.5f, 0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}, color },
		{ {-0.5f, 0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, color },
		{ {-0.5f, -0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, color },
		{ {-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}, color },

		// top
		{ {-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}, color },
		{ {0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}, color },
		{ {-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}, color },
		{ {0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}, color },

		// bot
		{ { 0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}, color },
		{ {-0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}, color },
		{ { 0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}, color },
		{ {-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}, color },
	};

	uint32_t indices[] =
	{
		0, 1, 2,
		3, 2, 1,

		4, 5, 6,
		7, 6, 5,
		
		8, 9, 10,
		11, 10, 9,

		12, 13, 14,
		15, 14, 13,

		16, 17, 18,
		19, 18, 17,

		20, 21, 22,
		23, 22, 21
	};

	
	mesh.vertexCount = ArrayCount(vertices);
	mesh.indexCount = ArrayCount(indices);
	mesh.vertices = Arena_PushArray(arena, mesh.vertexCount, Vertex);
	mesh.indices =	Arena_PushArray(arena, mesh.indexCount, uint32_t);

	memcpy(mesh.vertices, vertices, sizeof(vertices));
	memcpy(mesh.indices, indices, sizeof(indices));

	return mesh;
}

void Mesh_ApplyTransform(Mesh *mesh, Matrix4 transform)
{
	for (size_t i = 0; i < mesh->vertexCount; i++)
	{
		mesh->vertices[i].position = Matrix4_Multiply_Point3(transform, mesh->vertices[i].position);
	}
}

Mesh Mesh_Combine(Arena *arena, Mesh *meshA, Mesh *meshB)
{
	Mesh mesh = { 0 };
	mesh.vertexCount = meshA->vertexCount + meshB->vertexCount;
	mesh.indexCount = meshA->indexCount + meshB->indexCount;
	mesh.vertices = Arena_PushArray(arena, mesh.vertexCount, Vertex);
	mesh.indices =	Arena_PushArray(arena, mesh.indexCount, uint32_t);

	memcpy(mesh.vertices, meshA->vertices, meshA->vertexCount * sizeof(*mesh.vertices));
	memcpy(mesh.vertices + meshA->vertexCount, meshB->vertices, meshB->vertexCount * sizeof(*mesh.vertices));

	memcpy(mesh.indices, meshA->indices, meshA->indexCount * sizeof(*mesh.indices));
	for (size_t i = 0; i < meshB->indexCount; i++)
	{
		mesh.indices[meshA->indexCount + i] = meshA->vertexCount + meshB->indices[i];
	}
	return mesh;
}
