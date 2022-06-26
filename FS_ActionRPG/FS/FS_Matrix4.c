#include "FS_Matrix4.h"

#include <stdint.h>
#include <string.h> // memcopy

void Matrix4_Create(Matrix4 m, float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33)
{
	m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
	m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
	m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
	m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
}

void Matrix4_Identity(Matrix4 m)
{
	m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
	m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = 0;
	m[2][0] = 0; m[2][1] = 0; m[2][2] = 1; m[2][3] = 0;
	m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
}

void Matrix4_Zero(Matrix4 m)
{
	m[0][0] = 0; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
	m[1][0] = 0; m[1][1] = 0; m[1][2] = 0; m[1][3] = 0;
	m[2][0] = 0; m[2][1] = 0; m[2][2] = 0; m[2][3] = 0;
	m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 0;
}

void Matrix4_Copy(Matrix4 res, Matrix4 m)
{
	memcpy(res, m, sizeof(Matrix4));
}

void Matrix4_Transpose(Matrix4 res, Matrix4 m)
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			res[i][j] = m[j][i];
		}
	}
}

bool Matrix4_Inverse(Matrix4 res, Matrix4 src)
{
    float m[16];
    memcpy(m, src, sizeof(Matrix4));
    float inv[16];

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

    if (det == 0.0f)
        return false;

    det = 1.0f / det;
    Matrix4_Multiply_F(res, (Matrix4Row*)inv, det);

    return true;
}

void Matrix4_Add(Matrix4 res, Matrix4 a, Matrix4 b)
{
	Matrix4 temp;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			temp[i][j] = a[i][j] + b[i][j];
		}
	}
	Matrix4_Copy(res, temp);
}

void Matrix4_Subtract(Matrix4 res, Matrix4 a, Matrix4 b)
{
	Matrix4 temp;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			temp[i][j] = a[i][j] - b[i][j];
		}
	}
	Matrix4_Copy(res, temp);
}

void Matrix4_Multiply_M4(Matrix4 res, Matrix4 a, Matrix4 b)
{
	Matrix4 temp;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			temp[i][j] =
				  a[i][0] * b[0][j]
				+ a[i][1] * b[1][j]
				+ a[i][2] * b[2][j]
				+ a[i][3] * b[3][j];
		}
	}
	Matrix4_Copy(res, temp);
}

void Matrix4_Multiply_F(Matrix4 res, Matrix4 m, float s)
{
	Matrix4 temp;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			temp[i][j] = m[i][j] * s;
		}
	}
	Matrix4_Copy(res, temp);
}

Vector4 Matrix4_Multiply_V4(Matrix4 m, Vector4 v)
{
    Vector4 res;
    for (size_t i = 0; i < 4; i++)
    {
        (&res.x)[i] =
              m[i][0] * v.x
            + m[i][1] * v.y
            + m[i][2] * v.y
            + m[i][3] * v.w;
    }
    return res;
}

Vector3 Matrix4_Multiply_Point3(Matrix4 m, Vector3 p)
{
    Vector4 point = { p.x, p.y, p.z, 1.0f };
    Vector4 transformed = Matrix4_Multiply_V4(m, point);
    return Vector3_From_V4(transformed);
}

Vector3 Matrix4_Multiply_Direction3(Matrix4 m, Vector3 d)
{
    Vector4 dir = { d.x, d.y, d.z, 0.0f };
    Vector4 transformed = Matrix4_Multiply_V4(m, dir);
    return Vector3_From_V4(transformed);
}

void Matrix4_LookAt(Matrix4 m, Vector3 eye, Vector3 target)
{
	Vector3 z = Vector3_Direction(eye, target);
	Vector3 x = Vector3_Normalized(Vector3_Cross(z, (Vector3){0, 1, 0}));
	Vector3 y = Vector3_Normalized(Vector3_Cross(x, z));

	z = Vector3_Multiply_F(z, -1.0f);

	Matrix4_Create(m,
		x.x, x.y, x.z, -Vector3_Dot(eye, x),
		y.x, y.y, y.z, -Vector3_Dot(eye, y),
		z.x, z.y, z.z, -Vector3_Dot(eye, z),
		0, 0, 0, 1
	);
}

void Matrix4_Orthographic(Matrix4 m, float l, float r, float t, float b, float n, float f)
{
	Matrix4_Create(m,
		2.0f / (r - l), 0, 0, -(r + l) / (r - l),
		0, 2.0f / (t - b), 0, -(t + b) / (t - b),
		0, 0, -2.0f / (f - n), -(f + n) / (f - n),
		0, 0, 0, 1
	);
}

void Matrix4_Frustum(Matrix4 m, float l, float r, float t, float b, float n, float f)
{
	Matrix4_Create(m,
		(2.0f * n) / (r - l), 0, (r + l) / (r - l), 0,
		0, (2.0f * n) / (t - b), (t + b) / (t - b), 0,
		0, 0, -(f + n) / (f - n), -(2.0f * f * n) / (f - n),
		0, 0, -1, 0
	);
}

void Matrix4_Perspective(Matrix4 m, float fovy, float aspect, float near, float far)
{
	float top = Mathf_Tan(fovy / 2.0f) * near;
	float bot = -top;
	float right = top * aspect;
	float left = bot * aspect;

	Matrix4_Frustum(m, left, right, top, bot, near, far);
}
