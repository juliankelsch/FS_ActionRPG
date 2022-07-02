#include "FS_RenderList2D.h"
#include "FS_Macros.h"
#include "FS_String.h"
#include "FS_Debug.h"

void RenderList2D_Init(RenderList2D *renderList, Arena *arena, Rect bounds, uint32_t drawCallMax, uint32_t vertexMax, uint32_t indexMax)
{
	renderList->drawCalls = Arena_PushArray(arena, drawCallMax, DrawCall2D);
	renderList->vertices = Arena_PushArray(arena, vertexMax, Vertex2D);
	renderList->indices = Arena_PushArray(arena, indexMax, uint32_t);

	renderList->drawCallCount = 0;
	renderList->vertexCount = 0;
	renderList->indexCount = 0;

	renderList->drawCallMax = drawCallMax;
	renderList->vertexMax = vertexMax;
	renderList->indexMax = indexMax;

	renderList->bounds = bounds;
}

void RenderList2D_AddDrawCall(RenderList2D *renderList, DrawCall2D drawCall)
{
	if (renderList->drawCallCount < renderList->drawCallMax)
	{
		renderList->drawCalls[renderList->drawCallCount++] = drawCall;
	}
	else
	{
		Debug_Warn("RenderList2D -> Max draw calls reached.");
	}
}

void RenderList2D_AddVertices(RenderList2D *renderList, uint32_t vertexCount, Vertex2D *vertices)
{
	uint32_t copyCount = vertexCount;
	if (renderList->vertexCount + vertexCount >= renderList->vertexMax)
	{
		copyCount = renderList->vertexMax - renderList->vertexCount;
		Debug_Warn("RenderList2D -> Max vertices reached.");
	}

	CopyArray(renderList->vertices + renderList->vertexCount, vertices, copyCount, Vertex2D);
	renderList->vertexCount += copyCount;
}

void RenderList2D_AddIndices(RenderList2D *renderList, uint32_t indexCount, uint32_t *indices, uint32_t offset)
{
	uint32_t copyCount = indexCount;
	if (renderList->indexCount + indexCount >= renderList->indexMax)
	{
		copyCount = renderList->indexMax - renderList->indexCount;
		Debug_Warn("RenderList2D -> Max indices reached.");
	}

	for (uint32_t i = 0; i < copyCount; i++)
	{
		renderList->indices[renderList->indexCount++] = indices[i] + offset;
	}

	renderList->drawCalls[renderList->drawCallCount - 1].count += copyCount;
}

void RenderList2D_PushQuad(RenderList2D *renderList, Vector2 pos, Vector2 size, Color color, uint32_t texture)
{
	Vertex2D vertices[] =
	{
		{{pos.x, pos.y}, {0.0f, 1.0f}, color},
		{{pos.x + size.x, pos.y}, {1.0f, 1.0f}, color},
		{{pos.x, pos.y + size.y}, {0.0f, 0.0f}, color},
		{{pos.x + size.x, pos.y + size.y}, {1.0f, 0.0f}, color},
	};

	uint32_t indices[] =
	{ 
		2, 1, 0,
		1, 2, 3
	};
	RenderList2D_PushMesh(renderList, ArrayCount(vertices), vertices, ArrayCount(indices), indices, texture);
}

void RenderList2D_SetBounds(RenderList2D *renderList, Rect bounds)
{
	renderList->bounds = bounds;
}

void RenderList2D_Clear(RenderList2D *renderList)
{
	renderList->drawCallCount = 0;
	renderList->vertexCount = 0;
	renderList->indexCount = 0;
}

void RenderList2D_PushMesh(RenderList2D *renderList, uint32_t vertexCount, Vertex2D *vertices, uint32_t indexCount, uint32_t *indices, uint32_t texture)
{
	if (renderList->drawCallCount == 0)
	{
		RenderList2D_AddDrawCall(renderList, (DrawCall2D) { renderList->bounds, texture, 0, 0 });
	}
	else
	{
		DrawCall2D *currentCall = renderList->drawCalls + (renderList->drawCallCount - 1);
		if (currentCall->texture != texture)
		{
			DrawCall2D newCall = { renderList->bounds, texture, renderList->indexCount, 0 };
			RenderList2D_AddDrawCall(renderList, newCall);
		}
	}

	RenderList2D_AddIndices(renderList, indexCount, indices, renderList->vertexCount);
	RenderList2D_AddVertices(renderList, vertexCount, vertices);
}