#include "FS_Camera.h"

void Camera_CreateDefault(Camera *camera, uint32_t viewportWidth, uint32_t viewportHeight)
{
	camera->position = (Vector3){0, 4, 5};
	camera->target = (Vector3){0, 0, 0};
	camera->viewport = (RectInt){ 0, 0, viewportWidth, viewportHeight };
	camera->fovy = Mathf_Radians(70.0f);
	camera->near = 0.1f;
	camera->far = 100.0f;
}

void Camera_GetProjectionMatrix(Camera *camera, Matrix4 out)
{
	Matrix4_Perspective(out, camera->fovy, (float)camera->viewport.width / camera->viewport.height, camera->near, camera->far);
}

void Camera_GetViewMatrix(Camera *camera, Matrix4 out)
{
	Matrix4_LookAt(out, camera->position, camera->target);
}