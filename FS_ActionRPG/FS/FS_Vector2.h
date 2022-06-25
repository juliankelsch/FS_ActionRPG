#ifndef __FS_VECTOR2_H__
#define __FS_VECTOR2_H__

#include <stdint.h>

typedef struct
{
	int32_t x, y;
} Vector2Int;

typedef struct
{
	float x, y;
} Vector2;

Vector2 Vector2_Create(float x, float y);
Vector2 Vector2_Add(Vector2 a, Vector2 b);
Vector2 Vector2_Subtract(Vector2 a, Vector2 b);
Vector2 Vector2_Multiply(Vector2 a, Vector2 b);
float Vector2_Dot(Vector2 a, Vector2 b);

#endif // __FS_VECTOR2_H__