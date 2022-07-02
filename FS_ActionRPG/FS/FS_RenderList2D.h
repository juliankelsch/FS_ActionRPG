#ifndef __FS_RENDERLIST2D_H__
#define __FS_RENDERLIST2D_H__

#include <stdint.h>
#include <stdarg.h>

#include "FS_Arena.h"
#include "FS_Vertex2D.h"
#include "FS_Rectangle.h"

typedef struct
{
	Rect bounds;
	uint32_t texture;

	uint32_t first;
	uint32_t count;
} DrawCall2D;

typedef struct
{
	DrawCall2D *drawCalls;
	uint32_t drawCallCount;
	uint32_t drawCallMax;

	Vertex2D *vertices;
	uint32_t vertexCount;
	uint32_t vertexMax;

	uint32_t *indices;
	uint32_t indexCount;
	uint32_t indexMax;

	Rect bounds;
} RenderList2D;

void RenderList2D_Init(RenderList2D *renderList, Arena *arena, Rect bounds, uint32_t drawCallMax, uint32_t vertexMax, uint32_t indexMax);
void RenderList2D_PushMesh(RenderList2D *renderList, uint32_t vertexCount, Vertex2D *vertices, uint32_t indexCount, uint32_t *indices, uint32_t texture);
void RenderList2D_Clear(RenderList2D *renderList);
void RenderList2D_SetBounds(RenderList2D *renderList, Rect bounds);

void RenderList2D_PushQuad(RenderList2D *renderList, Vector2 pos, Vector2 size, Color color, uint32_t texture);

void RenderList2D_AddDrawCall(RenderList2D *renderList, DrawCall2D drawCall);
void RenderList2D_AddVertices(RenderList2D *renderList, uint32_t vertexCount, Vertex2D *vertices);
void RenderList2D_AddIndices(RenderList2D *renderList, uint32_t indexCount, uint32_t *indices, uint32_t offset);


#endif // __FS_RENDERLIST2D_H__