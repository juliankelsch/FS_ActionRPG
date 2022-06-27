#include "FS_Mesh.h"
#include "FS_Macros.h"
#include "FS_Debug.h"

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
			vertex->texCoords = (Vector2){ (float)j / (edgeCount - 1), (float)i / (edgeCount - 1) };
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

Mesh Mesh_CreateSphere(Arena *arena, uint32_t horizontalSlices, uint32_t verticalSlices)
{
	Debug_Assert(horizontalSlices > 0);
	Debug_Assert(verticalSlices > 2);

	const float radius = 0.5f;

	Mesh mesh = { 0 };
	mesh.vertexCount = (horizontalSlices + 2) * verticalSlices;
	mesh.indexCount = horizontalSlices * verticalSlices * 6;
	mesh.vertices = Arena_PushArray(arena, mesh.vertexCount, Vertex);
	mesh.indices =	Arena_PushArray(arena, mesh.indexCount, uint32_t);

	Color color = { 255, 255, 255, 255 };

	Vertex *vertex = mesh.vertices;

	for (size_t i = 0; i < horizontalSlices + 2; i++)
	{
		for (size_t j = 0; j < verticalSlices; j++)
		{
			float phi = ((float)j / (verticalSlices - 1) - 0.5f) * 2 * Mathf_Pi;
			float theta = ((float)i / (horizontalSlices + 1) - 0.5f) * Mathf_Pi;

			vertex->position = (Vector3){
				radius * Mathf_Cos(theta) * Mathf_Sin(phi),
				radius * Mathf_Sin(theta),
				radius * Mathf_Cos(theta) * Mathf_Cos(phi)
			};

			vertex->normal = Vector3_Normalized(vertex->position);
			vertex->color = color;
			vertex->texCoords = (Vector2){(float)i / (horizontalSlices - 1), (float)j / (verticalSlices - 1)};

			vertex++;
		}
	}

	uint32_t *index = mesh.indices;
	for (size_t i = 0; i < horizontalSlices + 1; i++)
	{
		for (size_t j = 0; j < verticalSlices - 1; j++)
		{
			size_t topRight = i * verticalSlices + j;
			size_t topLeft = topRight + 1;
			size_t botRight = (i + 1) * verticalSlices + j;
			size_t botLeft = botRight + 1;

			// TODO: Make separate loops for the caps instead of checking inside the loop
			if (i == 0)
			{
				*index++ = topRight;
				*index++ = botLeft;
				*index++ = botRight;
			}
			else if (i == horizontalSlices)
			{
				*index++ = topLeft;
				*index++ = botLeft;
				*index++ = topRight;
			}
			else
			{
				*index++ = topLeft;
				*index++ = botLeft;
				*index++ = topRight;

				*index++ = topRight;
				*index++ = botLeft;
				*index++ = botRight;
			}
		}
	}

	return mesh;
}

Mesh Mesh_CreateCircle(Arena *arena, float radius, uint32_t segments)
{
	Debug_Assert(segments > 2);
	Mesh mesh = { 0 };

	mesh.vertexCount = segments + 1;
	mesh.indexCount = segments * 3;
	mesh.vertices = Arena_PushArray(arena, mesh.vertexCount, Vertex);
	mesh.indices =	Arena_PushArray(arena, mesh.indexCount, uint32_t);
	Color color = { 255, 255, 255, 255 };

	Vertex *vertex = mesh.vertices;
	vertex->position = Vector3_Zero;
	vertex->normal = (Vector3){0, 1, 0};
	vertex->color = color;
	vertex->texCoords = (Vector2){0.5f, 0.5f};
	vertex++;

	for (size_t i = 0; i < segments; i++)
	{
		float angle = ((float)i / (segments - 1)) * 2 * Mathf_Pi;

		vertex->position = (Vector3){ radius * Mathf_Cos(angle), 0.0f, radius * Mathf_Sin(angle)};
		vertex->normal = (Vector3){0, 1, 0};
		vertex->color = color;
		vertex->texCoords = (Vector2){Mathf_Cos(angle) * 0.5f + 0.5f, Mathf_Sin(angle) * 0.5f + 0.5f};
		vertex++;
	}

	uint32_t *index = mesh.indices;
	for (size_t i = 0; i < segments - 1; i++)
	{
		*index++ = i + 1;
		*index++ = 0;
		*index++ = i + 2;
	}

	return mesh;
}

Mesh Mesh_CreateCone(Arena *arena, float height, float radius, uint32_t segments)
{
	Debug_Assert(segments > 2);
	Mesh mesh = { 0 };

	mesh.vertexCount = segments + 2;
	mesh.indexCount = segments * 6;
	mesh.vertices = Arena_PushArray(arena, mesh.vertexCount, Vertex);
	mesh.indices =	Arena_PushArray(arena, mesh.indexCount, uint32_t);
	Color color = { 255, 255, 255, 255 };

	Vertex *vertex = mesh.vertices;
	vertex->position = Vector3_Zero;
	vertex->normal = (Vector3){0, 1, 0};
	vertex->color = color;
	vertex->texCoords = (Vector2){0.5f, 0.5f};
	vertex++;

	for (size_t i = 0; i < segments; i++)
	{
		float angle = ((float)i / (segments - 1)) * 2 * Mathf_Pi;

		vertex->position = (Vector3){ radius * Mathf_Cos(angle), 0.0f, radius * Mathf_Sin(angle)};
		vertex->normal = (Vector3){0, 1, 0};
		vertex->color = color;
		vertex->texCoords = (Vector2){Mathf_Cos(angle) * 0.5f + 0.5f, Mathf_Sin(angle) * 0.5f + 0.5f};
		vertex++;
	}

	vertex->position = (Vector3){0.0f, height, 0.0f};
	vertex->normal = (Vector3){0, 1, 0};
	vertex->color = color;
	vertex->texCoords = (Vector2){0.5f, 0.5f};
	vertex++;

	uint32_t *index = mesh.indices;
	for (size_t i = 0; i < segments - 1; i++)
	{
		*index++ = i + 1;
		*index++ = 0;
		*index++ = i + 2;

		*index++ = i + 2;
		*index++ = i + 1;
		*index++ = segments + 1;
	}

	return mesh;
}

Mesh Mesh_CreateCylinder(Arena *arena, float height, float radius, uint32_t segments)
{
	Debug_Assert(segments > 2);

	Mesh mesh = { 0 };
	mesh.vertexCount = (segments + 1) * 2 + segments * 6;
	mesh.indexCount = segments * 12;
	mesh.vertices = Arena_PushArray(arena, mesh.vertexCount, Vertex);
	mesh.indices =	Arena_PushArray(arena, mesh.indexCount, uint32_t);
	Color color = { 255, 255, 255, 255 };

	Vertex *vertex = mesh.vertices;
	vertex->position = Vector3_Zero;
	vertex->normal = (Vector3){0, 1, 0};
	vertex->color = color;
	vertex->texCoords = (Vector2){0.5f, 0.5f};
	vertex++;

	vertex->position = (Vector3){0.0f, height, 0.0f};
	vertex->normal = (Vector3){0, 1, 0};
	vertex->color = color;
	vertex->texCoords = (Vector2){0.5f, 0.5f};
	vertex++;

	for (size_t i = 0; i < segments; i++)
	{
		float angle = ((float)i / (segments - 1)) * 2 * Mathf_Pi;

		vertex->position = (Vector3){ radius * Mathf_Cos(angle), 0.0f, radius * Mathf_Sin(angle)};
		vertex->normal = (Vector3){0, 1, 0};
		vertex->color = color;
		vertex->texCoords = (Vector2){Mathf_Cos(angle) * 0.5f + 0.5f, Mathf_Sin(angle) * 0.5f + 0.5f};
		vertex++;
	}

	for (size_t i = 0; i < segments; i++)
	{
		float angle = ((float)i / (segments - 1)) * 2 * Mathf_Pi;

		vertex->position = (Vector3){ radius * Mathf_Cos(angle), height, radius * Mathf_Sin(angle)};
		vertex->normal = (Vector3){0, 1, 0};
		vertex->color = color;
		vertex->texCoords = (Vector2){Mathf_Cos(angle) * 0.5f + 0.5f, Mathf_Sin(angle) * 0.5f + 0.5f};
		vertex++;
	}

	uint32_t *index = mesh.indices;
	for (size_t i = 0; i < segments - 1; i++)
	{
		// bot cap
		*index++ = i + 2;
		*index++ = i + 3;
		*index++ = 0;

		// side quad
		*index++ = segments + i + 3;
		*index++ = i + 2;
		*index++ = segments + i + 2;

		*index++ = segments + i + 3;
		*index++ = i + 3;
		*index++ = i + 2;

		// top cap
		*index++ = segments + i + 2;
		*index++ = 1;
		*index++ = segments + i + 3;
	}

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
