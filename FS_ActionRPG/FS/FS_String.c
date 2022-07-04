#include "FS_String.h"

#include <string.h>

void Copy(const void *dest, const void *src, uint32_t size)
{
	memcpy(dest, src, size);
}

void Move(const void *dest, const void *src, uint32_t size)
{
	memmove(dest, src, size);
}

bool StringBuffer_AppendChar(StringBuffer *string, Char c)
{
	if (string->used < string->size)
	{
		string->chars[string->used++] = c;
		return true;
	}
	return false;
}

bool StringBuffer_InsertCharAt(StringBuffer *string, uint32_t at, Char c)
{
	if (at <= string->used && string->used < string->size)
	{
		Move(string->chars + at + 1, string->chars + at, string->used - at);
		string->chars[at] = c;
		string->used++;
		return true;
	}
	return false;
}

bool StringBuffer_RemoveCharAt(StringBuffer *string, uint32_t at)
{
	if (at < string->used && string->used > 0)
	{
		Move(string->chars + at, string->chars + at + 1, string->used - at - 1);
		string->used--;
		return true;
	}
	return false;
}

bool StringBuffer_AppendString(StringBuffer *buffer, Char *string, uint32_t stringLength)
{
	if (buffer->used + stringLength <= buffer->size)
	{
		Copy(buffer->chars + buffer->used, string, stringLength);
		return true;
	}
	return false;
}

void StringBuffer_Clear(StringBuffer *buffer)
{
	buffer->used = 0;
}
