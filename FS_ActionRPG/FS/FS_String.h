#ifndef __FS_STRING_H__
#define __FS_STRING_H__

#include <stdbool.h>
#include <stdint.h>

typedef char Char;

typedef struct
{
	char *chars;
	uint32_t length;
} String;

#define CopyArray(dest, src, count, Type) Copy(dest, src, (count) *sizeof(Type))
void Copy(const void *dest, const void *src, uint32_t size);
void Move(const void *dest, const void *src, uint32_t size);

typedef struct
{
	Char *chars;
	uint32_t size;
	uint32_t used;
} StringBuffer;

bool StringBuffer_AppendChar(StringBuffer *string, Char c);
bool StringBuffer_InsertCharAt(StringBuffer *string, uint32_t at, Char c);
bool StringBuffer_RemoveCharAt(StringBuffer *string, uint32_t at);
bool StringBuffer_AppendString(StringBuffer *buffer, Char *string, uint32_t stringLength);
void StringBuffer_Clear(StringBuffer *buffer);

#endif // __FS_STRING_H__