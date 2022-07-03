#ifndef __FS_CAMERA_H__
#define __FS_CAMERA_H__

#include "FS_Vector3.h"
#include "FS_Matrix4.h"
#include "FS_Rectangle.h"

typedef struct
{
	Vector3 position;
	Vector3 target;

	RectInt viewport;
	float fovy;
	float near, far;
} Camera;

void Camera_CreateDefault(Camera *camera, uint32_t viewportWidth, uint32_t viewportHeight);
void Camera_GetProjectionMatrix(Camera *camera, Matrix4 out);
void Camera_GetViewMatrix(Camera *camera, Matrix4 out);
Vector3 Camera_Y(Camera *camera);
Vector3 Camera_X(Camera *camera);
Vector3 Camera_Z(Camera *camera);

#endif // __FS_CAMERA_H__
