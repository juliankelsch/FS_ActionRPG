#ifndef __FS_ARENA_H__
#define __FS_ARENA_H__

#include <stdint.h>
#include <stddef.h>

#define ALIGNMENT_OF(Type) offsetof(struct {Type t; char x; }, x)

typedef struct
{
	void *base;
	uint32_t size;
	uint32_t used;
} Arena;

Arena *Arena_Create(uint32_t arenaSize);
#define Arena_Push(arena, T) (T*)Arena_PushBytes(arena, sizeof(T))
#define Arena_PushArray(arena, count, T) (T*)Arena_PushBytes(arena, (count) * sizeof(T))
void *Arena_PushBytes(Arena *arena, uint32_t bytes);
void Arena_Reset(Arena *arena);

#endif // __FS_ARENA_H__
