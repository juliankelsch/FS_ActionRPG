#include "FS_String.h"

#include <string.h>

void Copy(const void *dest, const void *src, uint32_t size)
{
	memcpy(dest, src, size);
}