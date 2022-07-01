#ifndef __FS_OPENGL_H__
#define __FS_OPENGL_H__

#include <GLFW/glfw3.h>

#include <stdarg.h>

#include "FS_Camera.h"
#include "FS_Texture2D.h"
#include "FS_Mesh.h"
#include "FS_Font.h"
#include "FS_Transform.h"

void OpenGL_ApplyCamera(Camera *camera);
GLuint OpenGL_CreateTexture(Texture2D *texture);
void OpenGL_DrawMesh(Mesh *mesh);
void OpenGL_DrawMesh_Colored(Mesh *mesh, Color color);
void OpenGL_DrawMeshPoints(Mesh *mesh);
void OpenGL_AssignFontTexture(TrueTypeFont *font);
void OpenGL_DrawText(TrueTypeFont *font, float x, float y, const char *format, ...);

#endif // __FS_OPENGL_H__