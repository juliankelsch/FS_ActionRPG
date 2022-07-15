#include "FS_Camera.h"

void Camera_CreateDefault(Camera *camera, uint32_t viewportWidth, uint32_t viewportHeight)
{
	camera->position = (vec3){0, 4, 5};
	camera->target = (vec3){0, 0, 0};
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

vec3 Camera_Y(Camera *camera)
{
	vec3 z = Camera_Z(camera);;
	vec3 x = vec3_normalized_safe(vec3_cross(z, vec3_y));
	return vec3_normalized_safe(vec3_cross(x, z));
}

vec3 Camera_X(Camera *camera)
{

	vec3 z = Camera_Z(camera);;
	return vec3_normalized_safe(vec3_cross(z, vec3_y));
}

vec3 Camera_Z(Camera *camera)
{
	return vec3_direction(camera->target, camera->position);
}
