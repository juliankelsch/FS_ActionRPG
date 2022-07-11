#include "FS_String.h"

#include <string.h>

const char *String_SkipWhitespace(const char *at)
{
	while (*at && Char_IsWhitespace(*at))
	{
		at++;
	}
	return at;
}

bool String_Matches(String string, const char *b)
{
	if (!string.chars || !b)
		return false;

	for (size_t i = 0; i < string.length; i++)
	{
		if (!b[i] || b[i] != string.chars[i])
			return false;
	}
	return b[string.length] == 0;
}

bool String_Equals(const char *a, const char *b)
{
	if (!a || !b)
	{
		return false;
	}

	while (*a && *b)
	{
		if (*a != *b)
		{
			break;
		}
		a++;
		b++;
	}
	return *a == *b;
}

void Copy(const void *dest, const void *src, uint32_t size)
{
	memcpy(dest, src, size);
}

void Move(const void *dest, const void *src, uint32_t size)
{
	memmove(dest, src, size);
}

int Compare(const void *a, const void *b, uint32_t size)
{
	return memcmp(a, b, size);
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

bool Char_IsWhitespace(Char c)
{
	return c == ' '
		|| c == '\n'
		|| c == '\t'
		|| c == '\r'
		|| c == '\v'
		|| c == '\f';
}

bool Char_IsDigit(Char c)
{
	return c >= '0' && c <= '9';
}

bool Char_IsAlpha(Char c)
{
	Char lower = Char_ToLower(c);
	return lower >= 'a' && lower <= 'z';
}

bool Char_IsIdentifier(Char c)
{
	return Char_IsAlpha(c)
		|| Char_IsDigit(c)
		|| c == '_';
}

bool Char_IsUpper(Char c)
{
	return c >= 'A' && c <= 'Z';
}

bool Char_IsLower(Char c)
{
	return c >= 'a' && c <= 'z';
}

Char Char_ToUpper(Char c)
{
	return c + (Char_IsLower(c) * ('A' - 'a'));
}

Char Char_ToLower(Char c)
{
	return c + (Char_IsUpper(c) * ('a' - 'A'));
}
