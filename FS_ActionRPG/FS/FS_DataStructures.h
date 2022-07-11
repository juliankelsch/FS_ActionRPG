#ifndef __FS_DATA_STRUCTURES_H__
#define __FS_DATA_STRUCTURES_H__

#include <stdint.h>
#include <stdbool.h>

typedef void *AllocateFunc(void *data, size_t size);
typedef void DeallocateFunc(void *data, void *memory);

typedef struct Allocator
{
	void *data;
	AllocateFunc *allocate;
	DeallocateFunc *deallocate;
} Allocator;

Allocator *Allocator_GetDefault();

#define Allocator_Allocate(alloc, size) (alloc)->allocate((alloc)->data, (size))
#define Allocator_Deallocate(alloc, memory) (alloc)->deallocate((alloc)->data, (memory))
void *Allocator_Reallocate(Allocator *allocator, void *memory, size_t newSize);

typedef int32_t CompareFunc(void *a, void *b, void *userData);

void Algorithm_InsertionSort(void *elements, size_t elementCount, size_t elementSize, CompareFunc *compare, void *userData);

typedef struct List
{
	uint32_t count;
	uint32_t max;

	Allocator *allocator;

	size_t elementSize;

	void *data;
} List;

typedef void Action(void *params, void *userData);
typedef bool Predicate(void *params, void *userData);

void List_Init(List *list, size_t elementSize);
void List_InitWithAllocator(List *list, size_t elementSize, Allocator *allocator);

void *List_At(List *list, uint32_t index);
void List_Append(List *list, void *element, size_t elementSize);
void List_InsertAt(List *list, uint32_t index, void *element, size_t elementSize);
void List_RemoveAt(List *list, uint32_t index);
void List_Clear(List *list);

bool List_Contains(List *list, void *element, size_t elementSize);
int32_t List_Find(List *list, void *element, size_t elementSize);
int32_t List_FindAt(List *list, uint32_t start, uint32_t count, void *element, size_t elementSize);
int32_t List_FindIf(List *list, Predicate *predicate, void *userData);
int32_t List_FindIfAt(List *list, uint32_t start, uint32_t count, Predicate *predicate, void *userData);
void List_RemoveAll(List *list, void *element, size_t elementSize);
void List_RemoveIf(List *list, Predicate *predicate, void *userData);
void List_RemoveIfAt(List *list, uint32_t start, uint32_t count, Predicate *predicate, void *userData);


void List_ForEach(List *list, Action *action, void *userData);
void List_Sort(List *list, CompareFunc *compare, void *userData);

#endif // __FS_DATA_STRUCTURES_H__