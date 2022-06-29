#include "FS_Transform.h"

void Transform_Create(Transform *transform)
{
	transform->position = (Vector3){0, 0, 0};
	transform->rotation = (Quaternion){1, 0, 0, 0};
	transform->localScale = (Vector3){0, 0, 0};
}

void Transform_GetMatrix(Transform *transform, Matrix4 out)
{
	Matrix4 translation, rotation, localScale;
	Matrix4_Translation(translation, transform->position);
	Quaternion_ToMatrix(rotation, transform->rotation);
	Matrix4_Scale(localScale, transform->localScale);
	Matrix4 rs;
	Matrix4_Multiply(rs, rotation, localScale);
	Matrix4_Multiply(out, translation, rs);
}