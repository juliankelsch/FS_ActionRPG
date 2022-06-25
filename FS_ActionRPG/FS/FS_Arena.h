#ifndef __FS_ARENA_H__
#define __FS_ARENA_H__

#include <stdint.h>
#include <stdlib.h>
#include "FS_Debug.h"

#define ALIGNMENT_OF(Type) offsetof(struct {Type t; char x; }, x)

typedef struct
{
	void *base;
	uint32_t size;
	uint32_t used;
} Arena;

Arena *Arena_Create(uint32_t arenaSize);
#define Arena_Push(arena, T) (T*)Arena_PushBytes(arena, sizeof(T))
#define Arena_PushArray(arena, count, T) (T*)Arena_PushBytes(arena, count * sizeof(T))
void *Arena_PushBytes(Arena *arena, uint32_t bytes);
void Arena_Reset(Arena *arena);

// Implementation -----------------------------------------------------------------------------

Arena *Arena_Create(uint32_t arenaSize)
{
	uint8_t* memory = (uint8_t*)calloc(1, arenaSize + sizeof(Arena));
	if (memory == NULL)
	{
		Debug_Error("Failed to allocate memory for arena.");
		return NULL;
	}

	Arena *arena = (Arena*)memory;
	arena->size = arenaSize;
	arena->base = memory + sizeof(Arena);
	return arena;
}


void *Arena_PushBytes(Arena *arena, uint32_t bytes)
{
	if (arena->used + bytes > arena->size)
	{
		Debug_Error("Arena -> Allocation request exceeded arena size.");
		return NULL;
	}

	void *address = (uint8_t *)arena->base + arena->used;
	arena->used += bytes;
	return address;
}

void Arena_Reset(Arena *arena)
{
	arena->used = 0;
}



#endif // __FS_ARENA_H__
