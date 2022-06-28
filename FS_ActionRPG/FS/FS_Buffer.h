#ifndef __FS_BUFFER_H__
#define __FS_BUFFER_H__

#include <stdint.h>

typedef struct
{
	uint8_t *data;
	size_t size;
} Buffer;

#endif // __FS_BUFFER_H__