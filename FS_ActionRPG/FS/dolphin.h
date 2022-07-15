/*
	dolphin - v0.0 - public domain game math library - Julian Kelsch, 'github.com/juliankelsch/'

	This library is implemented as a single header library.
	Before including this header into your project

		#define DOLPHIN_IMPLEMTATION

	in *one* C or C++ file to create the implementation (example below).

		#include ...
		#include ...
		#include ...
		#define DOLPHIN_IMPLEMTATION
		#include "dolphin.h"


	// TODO

	FEATURES

	- 2, 3 and 4 dimensional vectors
	- matrices
	- quaternions
	- color math
	- geometry and intersection tests 
	- interpolation
	- bezier curves and splines
	- rectangle functions for ui math

	PHILOSOPY

	- easy to use
	- simplicity

	CODE STYLE

	- snake_case for anything but macros and ENUM values
*/

#ifndef __DOLPHIN_H__
#define __DOLPHIN_H__

#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h> // memcpy

union vec2
{
	struct { float x, y; };
	struct { float s, t; };
	struct { float width, height; };
	float e[2];
};

union vec3
{
	struct { float x, y, z; };
	struct { float s, t, __unused; };
	struct { float r, g, b; };
	float e[3];
};

union vec4
{
	struct { float x, y, z, w; };
	struct { float s, t, __unused0, __unused1; };
	struct { float r, g, b, a; };
	float e[4];
};

union mat4
{
	struct { vec4 rows[4]; };
	struct { float e[4][4]; };
	float values[16];
};

struct quat
{
	float s;
	vec3 v;
};

typedef union vec2 vec2;
typedef union vec3 vec3;
typedef union vec4 vec4;
typedef union mat4 mat4;

// math functions

float lerpf(float a, float b, float t);
float dotf(float *a, size_t step_a, float *b, size_t step_b, size_t count);

// vec3 functions

#define vec3_zero		(vec3){0.0f, 0.0f, 0.0f}
#define vec3_one		(vec3){1.0f, 1.0f, 1.0f}

#define vec3_x			(vec3){1.0f, 0.0f, 0.0f}
#define vec3_y			(vec3){0.0f, 1.0f, 0.0f}
#define vec3_z			(vec3){0.0f, 0.0f, 1.0f}

#define vec3_right		(vec3){ 1.0f,  0.0f,  0.0f}
#define vec3_left		(vec3){-1.0f,  0.0f,  0.0f}
#define vec3_up			(vec3){ 0.0f,  1.0f,  0.0f}
#define vec3_down		(vec3){ 0.0f, -1.0f,  0.0f}
#define vec3_forward	(vec3){ 0.0f,  0.0f,  1.0f}
#define vec3_back		(vec3){ 0.0f,  0.0f, -1.0f}

vec3 dolphin_vec3_add(vec3 a, vec3 b);
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

#define vec2_zero (vec2){0.0f, 0.0f}
#define vec2_x (vec2){0.0f, 0.0f}
#define vec2_y (vec2){0.0f, 1.0f}

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
vec2 vec2_normal(vec2 v);
vec2 vec2_multiply_f(vec2 v, float s);

#define mat4_id (mat4){	1, 0, 0, 0,\
						0, 1, 0, 0,\
						0, 0, 1, 0,\
						0, 0, 0, 1}

mat4 mat4_transpose(mat4 m);
mat4 mat4_inverse(mat4 m);

mat4 mat4_add(mat4 a, mat4 b);
mat4 mat4_subtract(mat4 a, mat4 b);
mat4 mat4_multiply(mat4 a, mat4 b);
mat4 mat4_multiply_f(mat4 m, float s);

mat4 mat4_translation(vec3 translation);
mat4 mat4_scale(vec3 scale);

vec4 mat4_multiply_vec4(mat4 m, vec4 p);

vec3 mat4_multiply_point3(mat4 m, vec3 p);
vec3 mat4_multiply_dir3(mat4 m, vec3 d);

mat4 mat4_change_of_basis(vec3 x, vec3 y, vec3 z);
mat4 mat4_change_of_basis_p(vec3 x, vec3 y, vec3 z, vec3 position);

mat4 mat4_look_at(vec3 eye, vec3 target);
mat4 mat4_ortho(float l, float r, float t, float b, float n, float f);
mat4 mat4_frustum(float l, float r, float t, float b, float n, float f);
mat4 mat4_perspective(float fovy, float aspect, float near, float far);

// TODO: Don't forget to take out
#define DOLPHIN_IMPLEMENTATION

#ifdef DOLPHIN_IMPLEMENTATION

float lerpf(float a, float b, float t)
{
	return (1.0f - t) * a + t * b;
}

float dotf(float *a, size_t step_a, float *b, size_t step_b, size_t count)
{
	float dot = 0.0f;
	for (size_t i = 0; i < count; i++)
	{
		dot += a[0] * b[0];
		a += step_a;
		b += step_b;
	}
	return dot;
}

// ==================================================================================

vec3 vec3_add(vec3 a, vec3 b)
{
	vec3 result = {
		a.x + b.x, 
		a.y + b.y,
		a.z + b.z
	};
	return result;
}

vec3 vec3_subtract(vec3 a, vec3 b)
{
	vec3 result = {
		a.x - b.x, 
		a.y - b.y,
		a.z - b.z
	};
	return result;
}

vec3 vec3_multiply(vec3 a, vec3 b)
{
	vec3 result = {
		a.x * b.x, 
		a.y * b.y,
		a.z * b.z
	};
	return result;
}

vec3 vec3_mulfiply_f(vec3 v, float s)
{
	vec3 result = {
		v.x * s,
		v.y * s,
		v.z * s
	};
	return result;
}

vec3 vec3_cross(vec3 a, vec3 b)
{
	vec3 result = {
		a.y * b.z - b.y * a.z,
		a.z * b.x - b.z * a.x,
		a.x * b.y - b.x * a.y
	};
	return result;
}

float vec3_dot(vec3 a, vec3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float vec3_length(vec3 v)
{
	return sqrtf(vec3_dot(v, v));
}

vec3 vec3_normalized(vec3 v)
{
	return vec3_mulfiply_f(v, 1.0f / vec3_length(v));
}

vec3 vec3_normalized_safe(vec3 v)
{
	float mag = vec3_length(v);
	if (mag != 0.0f)
	{
		return vec3_mulfiply_f(v, 1.0f / mag);
	}
	return v;
}

vec3 vec3_direction(vec3 a, vec3 b)
{
	return vec3_normalized_safe(vec3_subtract(b, a));
}

float vec3_distance(vec3 a, vec3 b)
{
	return vec3_length(vec3_subtract(a, b));
}

vec3 vec3_lerp(vec3 a, vec3 b, float t)
{
	vec3 res = {
		lerpf(a.x, b.x, t),
		lerpf(a.y, b.y, t),
		lerpf(a.z, b.z, t),
	};
	return res;
}

vec3 vec3_from_vec4(vec4 v)
{
	vec3 res = {
		v.x / v.w,
		v.y / v.w,
		v.z / v.w,
	};
	return res;
}

vec2 vec2_add(vec2 a, vec2 b)
{
	vec2 result = {
		a.x + b.x,
		a.y + b.y
	};
	return result;
}

vec2 vec2_subtract(vec2 a, vec2 b)
{
	vec2 result = {
		a.x - b.x,
		a.y - b.y
	};
	return result;
}

vec2 vec2_multiply(vec2 a, vec2 b)
{
	vec2 result = {
		a.x * b.x,
		a.y * b.y
	};
	return result;
}

float vec2_dot(vec2 a, vec2 b)
{
	return a.x * b.x + a.y * b.y;
}

float vec2_cross(vec2 a, vec2 b)
{
	return a.x * b.y - a.y * b.x;
}

float vec2_length(vec2 v)
{
	return sqrtf(vec2_dot(v, v));
}

float vec2_distance(vec2 a, vec2 b)
{
	return vec2_length(vec2_subtract(a, b));
}

vec2 vec2_direction(vec2 from, vec2 to)
{
	return vec2_normalized_safe(vec2_subtract(to, from));
}

vec2 vec2_multiply_f(vec2 v, float s)
{
	vec2 result = {
		v.x * s,
		v.y * s
	};
	return result;

}

vec2 vec2_normalized(vec2 v)
{
	return vec2_multiply_f(v, 1.0f / vec2_length(v));
}

vec2 vec2_normalized_safe(vec2 v)
{
	float mag = vec2_length(v);
	if (mag != 0.0f)
	{
		return vec2_multiply_f(v, 1.0f / mag);
	}

	return v;
}

vec2 vec2_normal(vec2 v)
{
	return vec2_normalized((vec2) { -v.y, v.x });
}

mat4 mat4_transpose(mat4 m)
{
	mat4 res;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			res.e[i][j] = m.e[j][i];
		}
	}
	return res;
}

mat4 mat4_inverse(mat4 original)
{
	mat4 inverse;

	float *m = original.values;
	float *inv = inverse.values;

    inv[0] = m[5] * m[10] * m[15] -
        m[5] * m[11] * m[14] -
        m[9] * m[6] * m[15] +
        m[9] * m[7] * m[14] +
        m[13] * m[6] * m[11] -
        m[13] * m[7] * m[10];

    inv[4] = -m[4] * m[10] * m[15] +
        m[4] * m[11] * m[14] +
        m[8] * m[6] * m[15] -
        m[8] * m[7] * m[14] -
        m[12] * m[6] * m[11] +
        m[12] * m[7] * m[10];

    inv[8] = m[4] * m[9] * m[15] -
        m[4] * m[11] * m[13] -
        m[8] * m[5] * m[15] +
        m[8] * m[7] * m[13] +
        m[12] * m[5] * m[11] -
        m[12] * m[7] * m[9];

    inv[12] = -m[4] * m[9] * m[14] +
        m[4] * m[10] * m[13] +
        m[8] * m[5] * m[14] -
        m[8] * m[6] * m[13] -
        m[12] * m[5] * m[10] +
        m[12] * m[6] * m[9];

    inv[1] = -m[1] * m[10] * m[15] +
        m[1] * m[11] * m[14] +
        m[9] * m[2] * m[15] -
        m[9] * m[3] * m[14] -
        m[13] * m[2] * m[11] +
        m[13] * m[3] * m[10];

    inv[5] = m[0] * m[10] * m[15] -
        m[0] * m[11] * m[14] -
        m[8] * m[2] * m[15] +
        m[8] * m[3] * m[14] +
        m[12] * m[2] * m[11] -
        m[12] * m[3] * m[10];

    inv[9] = -m[0] * m[9] * m[15] +
        m[0] * m[11] * m[13] +
        m[8] * m[1] * m[15] -
        m[8] * m[3] * m[13] -
        m[12] * m[1] * m[11] +
        m[12] * m[3] * m[9];

    inv[13] = m[0] * m[9] * m[14] -
        m[0] * m[10] * m[13] -
        m[8] * m[1] * m[14] +
        m[8] * m[2] * m[13] +
        m[12] * m[1] * m[10] -
        m[12] * m[2] * m[9];

    inv[2] = m[1] * m[6] * m[15] -
        m[1] * m[7] * m[14] -
        m[5] * m[2] * m[15] +
        m[5] * m[3] * m[14] +
        m[13] * m[2] * m[7] -
        m[13] * m[3] * m[6];

    inv[6] = -m[0] * m[6] * m[15] +
        m[0] * m[7] * m[14] +
        m[4] * m[2] * m[15] -
        m[4] * m[3] * m[14] -
        m[12] * m[2] * m[7] +
        m[12] * m[3] * m[6];

    inv[10] = m[0] * m[5] * m[15] -
        m[0] * m[7] * m[13] -
        m[4] * m[1] * m[15] +
        m[4] * m[3] * m[13] +
        m[12] * m[1] * m[7] -
        m[12] * m[3] * m[5];

    inv[14] = -m[0] * m[5] * m[14] +
        m[0] * m[6] * m[13] +
        m[4] * m[1] * m[14] -
        m[4] * m[2] * m[13] -
        m[12] * m[1] * m[6] +
        m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] +
        m[1] * m[7] * m[10] +
        m[5] * m[2] * m[11] -
        m[5] * m[3] * m[10] -
        m[9] * m[2] * m[7] +
        m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] -
        m[0] * m[7] * m[10] -
        m[4] * m[2] * m[11] +
        m[4] * m[3] * m[10] +
        m[8] * m[2] * m[7] -
        m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] +
        m[0] * m[7] * m[9] +
        m[4] * m[1] * m[11] -
        m[4] * m[3] * m[9] -
        m[8] * m[1] * m[7] +
        m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] -
        m[0] * m[6] * m[9] -
        m[4] * m[1] * m[10] +
        m[4] * m[2] * m[9] +
        m[8] * m[1] * m[6] -
        m[8] * m[2] * m[5];

    float det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

	assert(det != 0.0f);

    if (det == 0.0f)
        return original;

    return mat4_multiply_f(inverse, 1.0f / det);
}

mat4 mat4_add(mat4 a, mat4 b)
{
	mat4 res;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			res.e[i][j] = a.e[i][j] + b.e[i][j];
		}
	}
	return res;
}

mat4 mat4_subtract(mat4 a, mat4 b)
{
	mat4 res;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			res.e[i][j] = a.e[i][j] - b.e[i][j];
		}
	}
	return res;
}

mat4 mat4_multiply(mat4 a, mat4 b)
{
	mat4 product;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			product.e[i][j] =
				  a.e[i][0] * b.e[0][j]
				+ a.e[i][1] * b.e[1][j]
				+ a.e[i][2] * b.e[2][j]
				+ a.e[i][3] * b.e[3][j];
		}
	}
	return product;
}

mat4 mat4_multiply_f(mat4 m, float s)
{
	mat4 res;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			res.e[i][j] = m.e[i][j] * s;
		}
	}
	return res;
}

vec4 mat4_multiply_vec4(mat4 m, vec4 v)
{
    vec4 res;
    for (size_t i = 0; i < 4; i++)
    {
        res.e[i] =
              m.e[i][0] * v.x
            + m.e[i][1] * v.y
            + m.e[i][2] * v.z
            + m.e[i][3] * v.w;
    }
    return res;
}

vec3 mat4_multiply_point3(mat4 m, vec3 p)
{
    vec4 point = { p.x, p.y, p.z, 1.0f };
    vec4 transformed = mat4_multiply_vec4(m, point);
    return vec3_from_vec4(transformed);
}

vec3 mat4_multiply_dir3(mat4 m, vec3 d)
{
    vec4 dir = { d.x, d.y, d.z, 0.0f };
    vec4 transformed = mat4_multiply_vec4(m, dir);
    return vec3_from_vec4(transformed);
}

mat4 mat4_translation(vec3 t)
{
    return (mat4) {
        1, 0, 0, t.x,
        0, 1, 0, t.y,
        0, 0, 1, t.z,
        0, 0, 0, 1
    };
}

mat4 mat4_scale(vec3 s)
{
    return (mat4) {
        s.x, 0, 0, 0,
        0, s.y, 0, 0,
        0, 0, s.z, 0,
        0, 0, 0, 1
    };
}

mat4 mat4_change_of_basis(vec3 x, vec3 y, vec3 z)
{
	return (mat4) {
		x.x, y.x, z.x, 0,
		x.y, y.y, z.y, 0,
		x.z, y.z, z.z, 0,
		0, 0, 0, 1
	};
}

mat4 mat4_change_of_basis_p(vec3 x, vec3 y, vec3 z, vec3 p)
{
	return (mat4) {
		x.x, y.x, z.x, p.x,
		x.y, y.y, z.y, p.y,
		x.z, y.z, z.z, p.z,
		0, 0, 0, 1
	};
}

mat4 mat4_look_at(vec3 eye, vec3 target)
{
	vec3 z = vec3_direction(eye, target);
	vec3 x = vec3_normalized(vec3_cross(z, (vec3){0, 1, 0}));
	vec3 y = vec3_normalized(vec3_cross(x, z));

	z = vec3_mulfiply_f(z, -1.0f);

	return (mat4) {
		x.x, x.y, x.z, -vec3_dot(eye, x),
		y.x, y.y, y.z, -vec3_dot(eye, y),
		z.x, z.y, z.z, -vec3_dot(eye, z),
		0, 0, 0, 1
	};
}

mat4 mat4_ortho(float l, float r, float t, float b, float n, float f)
{
	return (mat4) {
		2.0f / (r - l), 0, 0, -(r + l) / (r - l),
		0, 2.0f / (t - b), 0, -(t + b) / (t - b),
		0, 0, -2.0f / (f - n), -(f + n) / (f - n),
		0, 0, 0, 1
	};
}

mat4 mat4_frustum(float l, float r, float t, float b, float n, float f)
{
	return (mat4) {
		(2.0f * n) / (r - l), 0, (r + l) / (r - l), 0,
		0, (2.0f * n) / (t - b), (t + b) / (t - b), 0,
		0, 0, -(f + n) / (f - n), -(2.0f * f * n) / (f - n),
		0, 0, -1, 0
	};
}

mat4 mat4_perspective(float fovy, float aspect, float near, float far)
{
	float top = tanf(fovy / 2.0f) * near;
	float bot = -top;
	float right = top * aspect;
	float left = bot * aspect;

	return mat4_frustum(left, right, top, bot, near, far);
}

// ==================================================================================

#endif // DOLPHIN_IMPLEMENTATION

#endif // __DOLPHIN_H__