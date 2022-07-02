#ifndef __FS_STRING_H__
#define __FS_STRING_H__

#include <stdint.h>

typedef struct
{
	char *Chars;
	uint32_t Length;
} String;

#define CopyArray(dest, src, count, Type) Copy(dest, src, (count) *sizeof(Type))
void Copy(const void *dest, const void *src, uint32_t size);

#endif // __FS_STRING_H__