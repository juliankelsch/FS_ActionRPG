#ifndef __FS_VEC3_H__
#define __FS_VEC3_H__

#include "FS_Vector4.h"
#include "FS_Mathf.h"

union vec3
{
	struct { float x, y, z; };
	struct { float s, t, __unused; };
	struct { float r, g, b; };
	float e[3];
};

typedef union vec3 vec3;

#define vec3_zero	(vec3){0.0f, 0.0f, 0.0f}
#define vec3_one		(vec3){1.0f, 1.0f, 1.0f}

#define vec3_x (vec3){1.0f, 0.0f, 0.0f}
#define vec3_y (vec3){0.0f, 1.0f, 0.0f}
#define vec3_z (vec3){0.0f, 0.0f, 1.0f}

#define vec3_right	(vec3){ 1.0f,  0.0f,  0.0f}
#define vec3_left	(vec3){-1.0f,  0.0f,  0.0f}
#define vec3_up		(vec3){ 0.0f,  1.0f,  0.0f}
#define vec3_down	(vec3){ 0.0f, -1.0f,  0.0f}
#define vec3_forward (vec3){ 0.0f,  0.0f,  1.0f}
#define vec3_back	(vec3){ 0.0f,  0.0f, -1.0f}

vec3 vec3_create(float x, float y, float z);
vec3 vec3_add(vec3 a, vec3 b);
vec3 vec3_subtract(vec3 a, vec3 b);
vec3 vec3_multiply(vec3 a, vec3 b);
vec3 vec3_mulfiply_f(vec3 v, float s);
vec3 vec3_cross(vec3 a, vec3 b);
float vec3_dot(vec3 a, vec3 b);
float vec3_length(vec3 v);
vec3 vec3_normalized(vec3 v);
vec3 vec3_normalized_safe(vec3 v);
vec3 vec3_direction(vec3 from, vec3 to);
float vec3_distance(vec3 a, vec3 b);
vec3 vec3_lerp(vec3 a, vec3 b, float t);
vec3 vec3_from_vec4(vec4 v);

#endif // __FS_VEC3_H__