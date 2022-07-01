#ifndef __FS_STRING_H__
#define __FS_STRING_H__

#include <stdint.h>

typedef struct
{
	char *Chars;
	uint32_t Length;
} String;

#endif // __FS_STRING_H__