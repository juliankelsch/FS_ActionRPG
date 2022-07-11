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

bool String_Matches(String string, const char *b);
bool String_Equals(const char *a, const char *b);
const char *String_SkipWhitespace(const char *at);

#define CopyArray(dest, src, count, Type) Copy(dest, src, (count) *sizeof(Type))
void Copy(const void *dest, const void *src, uint32_t size);
void Move(const void *dest, const void *src, uint32_t size);
int Compare(const void *a, const void *b, uint32_t size);

bool Char_IsDigit(Char c);
bool Char_IsAlpha(Char c);
bool Char_IsIdentifier(Char c); // a-z | A-Z | 0-9 | _
bool Char_IsUpper(Char c);
bool Char_IsLower(Char c);
bool Char_IsWhitespace(Char c);
Char Char_ToUpper(Char c);
Char Char_ToLower(Char c);

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