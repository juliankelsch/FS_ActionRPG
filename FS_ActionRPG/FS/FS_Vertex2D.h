#ifndef __FS_VERTEX2D_H__
#define __FS_VERTEX2D_H__

#include "FS_Vector2.h"
#include "FS_Color.h"

typedef struct
{
	Vector2 position;
	Vector2 texCoords;
	Color color;
} Vertex2D;


#endif // __FS_VERTEX2D_H__