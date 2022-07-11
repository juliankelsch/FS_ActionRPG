#include "FS_DataStructures.h"
#include "FS_Debug.h"
#include "FS_String.h"


#include <stdlib.h>

static void *Default_Allocate(void *data, size_t size)
{
	return calloc(1, size);
}

static void Default_Deallocate(void *data, void *memory)
{
	free(memory);
}

Allocator *Allocator_GetDefault()
{
	static Allocator alloc = {
		NULL, 
		Default_Allocate, 
		Default_Deallocate 
	};

	return &alloc;
}

void *Allocator_Reallocate(Allocator *allocator, void *memory, size_t newSize)
{
	void *newData = Allocator_Allocate(allocator, newSize);
	
	if (newData)
	{
		if (memory)
		{
			Copy(newData, memory, newSize);
			Allocator_Deallocate(allocator, memory);
		}
	}
	else
	{
		Debug_Error("Failed to reallocate memory.");
	}
	return newData;
}

void Algorithm_InsertionSort(void *elements, size_t elementCount, size_t elementSize, CompareFunc *compare, void *userData)
{
#define MAX_ELEMENT_SIZE 256 
	Debug_Assert(elementSize <= MAX_ELEMENT_SIZE);

	static char a[MAX_ELEMENT_SIZE];
	for (size_t i = 1; i < elementCount; i++)
	{
		Copy(a, (char *)elements + (i * elementSize), elementSize);
		for (size_t j = 0; j < i; j++)
		{
			void *b = (char *)elements + (j * elementSize);
			if (compare(a, b, userData) < 0)
			{
				Move((char *)elements + ((j + 1) * elementSize), b, (i - j) * elementSize);
				Copy(b, a, elementSize);
				break;
			}
		}
	}
}

void List_InitWithAllocator(List *list, size_t elementSize, Allocator *allocator)
{
	list->count = 0;
	list->max = 0;
	list->elementSize = elementSize;
	list->allocator = allocator;
	list->data = NULL;
}

void List_Init(List *list, size_t elementSize)
{
	list->count = 0;
	list->max = 0;
	list->elementSize = elementSize;
	list->allocator = Allocator_GetDefault();
	list->data = NULL;
}

void List_ForEach(List *list, Action *action, void *userData)
{
	for (size_t i = 0; i < list->count; i++)
	{
		action((char *)list->data + (i * list->elementSize), userData);
	}
}

static uint32_t List_Growth(List *list)
{
	return list->max * 1.5 + 4;
}

static bool List_TrySetCapacity(List *list, uint32_t newCapacity)
{
	void *newData = Allocator_Reallocate(list->allocator, list->data, newCapacity * list->elementSize);
	if (newData)
	{
		list->data = newData;
		list->max = newCapacity;
	}
	return newData != NULL;
}

static bool List_TryMakeSpace(List *list, uint32_t newElementCount)
{
	bool needsToGrow = list->count + newElementCount > list->max;
	if (needsToGrow)
	{
		uint32_t newMax = List_Growth(list);
		return List_TrySetCapacity(list, newMax);
	}
	return true;
}

static void List_SetElement(List *list, uint32_t index, void *element, size_t elementSize)
{
	Copy(List_At(list, index), element, elementSize);
}

void List_Append(List *list, void *element, size_t elementSize)
{
	Debug_Assert(elementSize == list->elementSize);

	if (List_TryMakeSpace(list, 1))
	{
		List_SetElement(list, list->count++, element, elementSize);
	}
}

static void *List_At(List *list, uint32_t index)
{
	return (char *)list->data + (index * list->elementSize);
}

void List_InsertAt(List *list, uint32_t index, void *element, size_t elementSize)
{
	Debug_Assert(elementSize == list->elementSize);
	Debug_Assert(index <= list->count);

	if (List_TryMakeSpace(list, 1))
	{
		Move(List_At(list, index + 1), List_At(list, index), (list->count - index) * elementSize);
		List_SetElement(list, index, element, elementSize);
		list->count++;
	}
}

void List_RemoveAt(List *list, uint32_t index)
{
	Debug_Assert(index < list->count);
	Move(List_At(list, index), List_At(list, index + 1), (list->count - index - 1) * list->elementSize);
	list->count--;
}


void List_Clear(List *list)
{
	list->count = 0;
	list->max = 0;
	Allocator_Deallocate(list->allocator, list->data);
}

bool List_Contains(List *list, void *element, size_t elementSize)
{
	Debug_Assert(elementSize == list->elementSize);

	for (size_t i = 0; i < list->count; i++)
	{
		if (Compare(element, List_At(list, i), elementSize) == 0)
		{
			return true;
		}
	}
	return false;
}

int32_t List_Find(List *list, void *element, size_t elementSize)
{
	Debug_Assert(elementSize == list->elementSize);
	return List_FindAt(list, 0, list->count, element, elementSize);
}

int32_t List_FindAt(List *list, uint32_t start, uint32_t count, void *element, size_t elementSize)
{
	Debug_Assert(elementSize == list->elementSize);
	Debug_Assert(start <= list->count);
	Debug_Assert(start + count <= list->count);

	for (uint32_t i = start; i < (start + count); i++)
	{
		if (Compare(element, List_At(list, i), elementSize) == 0)
		{
			return i;
		}
	}
	return -1;
	
}

void List_RemoveAll(List *list, void *element, size_t elementSize);
void List_RemoveIf(List *list, Predicate *predicate);

void List_Sort(List *list, CompareFunc *compare, void *userData)
{
	Algorithm_InsertionSort(list->data, list->count, list->elementSize, compare, userData);
}

