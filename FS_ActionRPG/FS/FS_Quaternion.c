#include "FS_Quaternion.h"

Quaternion Quaternion_Identity()
{
	Quaternion result = { 1.0f, 0.0f, 0.0f, 0.0f };
	return result;
}

Quaternion Quaternion_AxisAngle(float angle, vec3 axis)
{
	return (Quaternion) { Mathf_Sin(angle / 2.0f), vec3_mulfiply_f(vec3_normalized_safe(axis), angle / 2.0f) };
}

Quaternion Quaternion_Inverse(Quaternion quat)
{
	return Quaternion_Multiply_F(Quaternion_Conjugate(quat), (1.0f / Quaternion_Dot(quat, quat)));
}

Quaternion Quaternion_Conjugate(Quaternion quat)
{
	return (Quaternion){quat.s, vec3_mulfiply_f(quat.v, -1.0f) };
}

Quaternion Quaternion_Normalize(Quaternion quat)
{
	return Quaternion_Multiply_F(quat, 1.0f / Quaternion_Length(quat));
}

Quaternion Quaternion_FromMatrix(Matrix4 m)
{
    float s = Mathf_Sqrt(m[0][0] + m[1][1] + m[2][2] + 1) / 2.0f;
    vec3 v = {
		(m[2][1]  - m[1][2]) / (4.0f * s),
		(m[0][2] - m[2][0]) / (4.0f * s),
		(m[1][0] - m[0][1]) / (4.0f * s)
    };
    return (Quaternion){s, v};
}

void Quaternion_ToMatrix(Matrix4 matrix, Quaternion quat)
{
    float s = quat.s, x = quat.v.x, y = quat.v.y, z = quat.v.z;

    Matrix4 m = {1.0f - 2.0f * (y * y + z * z), 2.0f * (x * y - s * z), 2.0f * (s * y + x * z), 0.0f,
                  2.0f * (x * y + s * z), 1.0f - 2.0f * (x * x + z * z), 2.0f * (y * z - s * x), 0.0f,
                  2.0f * (x * z - s * y), 2.0f * (s * x + y * z), 1.0f - 2.0f * (x * x + y * y), 0.0f,
                  0.0f, 0.0f, 0.0f, 1.0f};
	// TODO: Avoid this copy
	Matrix4_Copy(matrix, m);
}

Quaternion Quaternion_Slerp(Quaternion a, Quaternion b, float t)
{
    float cos_half_theta = Quaternion_Dot(a, b);
    if (Mathf_Abs(cos_half_theta) >= 1.0)
    {
        return a;
    }

    Quaternion bb = b;
    if (cos_half_theta < 0.0f)
    {
        bb = Quaternion_Multiply_F(bb, -1.0f);
        cos_half_theta = -cos_half_theta;
    }

    float half_theta = Mathf_Acos(cos_half_theta);
    float sin_half_theta = Mathf_Sqrt(1.0f - cos_half_theta * cos_half_theta);
    if (Mathf_Abs(sin_half_theta) < 0.001)
    {
		return Quaternion_Multiply_F(Quaternion_Add(a, bb), 0.5f);
    }

    float ratio_a = Mathf_Sin((1.0f - t) * half_theta) / sin_half_theta;
    float ratio_b = Mathf_Sin((t) * half_theta) / sin_half_theta;
	return Quaternion_Add(Quaternion_Multiply_F(a, ratio_a), Quaternion_Multiply_F(b, ratio_b));
}

float Quaternion_Dot(Quaternion a, Quaternion b)
{
	return a.s * b.s + vec3_dot(a.v, b.v);
}

float Quaternion_Length(Quaternion quat)
{
	return Mathf_Sqrt(Quaternion_Dot(quat, quat));
}

vec3 Quaternion_Rotate(vec3 point, Quaternion quat)
{
	Quaternion p = { 0.0f, point };
	return Quaternion_Multiply(Quaternion_Multiply(quat, p), Quaternion_Conjugate(quat)).v;
}

Quaternion Quaternion_Add(Quaternion a, Quaternion b)
{
	return (Quaternion) { a.s + b.s, vec3_add(a.v, b.v) };
}

Quaternion Quaternion_Subtract(Quaternion a, Quaternion b)
{
	return (Quaternion) { a.s - b.s, vec3_subtract(a.v, b.v) };
}

Quaternion Quaternion_Multiply(Quaternion a, Quaternion b)
{
	return (Quaternion) {
		a.s * b.s - Quaternion_Dot(a, b),
		vec3_add
		(
			vec3_add
			(
				vec3_mulfiply_f(a.v, b.s),
				vec3_mulfiply_f(b.v, a.s)
			),
			vec3_cross(a.v, b.v)
		)
	};
}

Quaternion Quaternion_Multiply_F(Quaternion quat, float scalar)
{
	return (Quaternion) { quat.s * scalar, vec3_mulfiply_f(quat.v, scalar) };
}
