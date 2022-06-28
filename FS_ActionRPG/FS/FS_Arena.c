#include "FS_Arena.h"
#include "FS_Debug.h"

#include <stdlib.h>

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
