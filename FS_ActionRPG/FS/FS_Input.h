#ifndef __FS_INPUT_H__
#define __FS_INPUT_H__

#include "FS_Vector2.h"

typedef struct
{
	float time;
	float deltaTime;
} Time;

typedef struct
{
	Vector2 position;
} Mouse;

typedef struct
{
	bool dummy;
} Keyboard;

#endif // __FS_INPUT_H__