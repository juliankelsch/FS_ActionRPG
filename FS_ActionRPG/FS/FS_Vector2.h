#ifndef __FS_VECTOR2_H__
#define __FS_VECTOR2_H__

#include <stdint.h>

typedef struct
{
	int32_t x, y;
} vec2i;

typedef struct
{
	float x, y;
} vec2;

#define vec2_zero (vec2){0.0f, 0.0f}
#define vec2_x (vec2){0.0f, 0.0f}
#define vec2_y (vec2){0.0f, 1.0f}

vec2 vec2_create(float x, float y);
vec2 vec2_add(vec2 a, vec2 b);
vec2 vec2_subtract(vec2 a, vec2 b);
vec2 vec2_multiply(vec2 a, vec2 b);
float vec2_dot(vec2 a, vec2 b);
float vec2_cross(vec2 a, vec2 b);
float vec2_length(vec2 v);
float vec2_distance(vec2 a, vec2 b);
vec2 vec2_direction(vec2 from, vec2 to);
vec2 vec2_normalized(vec2 v);
vec2 vec2_normalized_safe(vec2 v);
vec2 vec2_nomal(vec2 v);
vec2 vec2_multiply_f(vec2 v, float s);

#endif // __FS_VECTOR2_H__