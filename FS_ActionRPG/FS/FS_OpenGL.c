#include "FS_OpenGL.h"

void OpenGL_ApplyCamera(Camera *camera)
{
	glViewport(camera->viewport.x, camera->viewport.y, camera->viewport.width, camera->viewport.height);

	Matrix4 projection, view;
	Camera_GetProjectionMatrix(camera, projection);
	Camera_GetViewMatrix(camera, view);

	Matrix4 oglProjection, oglView;
	Matrix4_Transpose(oglProjection, projection);
	Matrix4_Transpose(oglView, view);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(&oglProjection[0][0]);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(&oglView[0][0]);
}

GLuint OpenGL_CreateTexture(Texture2D *texture)
{
	GLuint id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	return id;
}

void OpenGL_DrawMesh(Mesh *mesh)
{
	glBegin(GL_TRIANGLES);
	for (size_t i = 0; i < mesh->indexCount; i++)
	{
		Vertex *vertex = mesh->vertices + mesh->indices[i];
		glColor4ub(vertex->color.r, vertex->color.g, vertex->color.b, vertex->color.a);
		glNormal3f(vertex->normal.x, vertex->normal.y, vertex->normal.z);
		glTexCoord2f(vertex->texCoords.x, vertex->texCoords.y);
		glVertex3f(vertex->position.x, vertex->position.y, vertex->position.z);
	}
	glEnd();
}

void OpenGL_DrawMesh_Colored(Mesh *mesh, Color color)
{
	glBegin(GL_TRIANGLES);
	for (size_t i = 0; i < mesh->indexCount; i++)
	{
		Vertex *vertex = mesh->vertices + mesh->indices[i];
		glColor4ub(color.r, color.g, color.b, color.a);
		glNormal3f(vertex->normal.x, vertex->normal.y, vertex->normal.z);
		glTexCoord2f(vertex->texCoords.x, vertex->texCoords.y);
		glVertex3f(vertex->position.x, vertex->position.y, vertex->position.z);
	}
	glEnd();
}

void OpenGL_DrawMeshPoints(Mesh *mesh)
{
	glBegin(GL_POINTS);
	for (size_t i = 0; i < mesh->vertexCount; i++)
	{
		Vertex *vertex = mesh->vertices + i;
		glColor4ub(vertex->color.r, vertex->color.g, vertex->color.b, vertex->color.a);
		glNormal3f(vertex->normal.x, vertex->normal.y, vertex->normal.z);
		glTexCoord2f(vertex->texCoords.x, vertex->texCoords.y);
		glVertex3f(vertex->position.x, vertex->position.y, vertex->position.z);
	}
	glEnd();
}

void OpenGL_AssignFontTexture(TrueTypeFont *font)
{
    glGenTextures(1, &font->textureID);
    glBindTexture(GL_TEXTURE_2D, font->textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, font->bitmap.width, font->bitmap.height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, font->bitmap.pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void OpenGL_DrawText(TrueTypeFont *font, float x, float y, const char *text)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, font->textureID);
    glBegin(GL_QUADS);

    while (*text) {
        if (*text >= font->firstChar && *text < (font->firstChar + font->charCount)) {
            stbtt_aligned_quad q;
            stbtt_GetBakedQuad(font->chars, font->bitmap.width, font->bitmap.height, *text - 32, &x, &y, &q, 1);//1=opengl & d3d10+,0=d3d9
            glTexCoord2f(q.s1, q.t0); glVertex2f(q.x1, q.y0);
            glTexCoord2f(q.s0, q.t0); glVertex2f(q.x0, q.y0);
            glTexCoord2f(q.s0, q.t1); glVertex2f(q.x0, q.y1);
            glTexCoord2f(q.s1, q.t1); glVertex2f(q.x1, q.y1);
        }
        ++text;
    }
    glEnd();
}

void OpenGL_ApplyTransform(Transform *transform)
{
	glTranslatef(transform->position.x, transform->position.y, transform->position.z);
	glScalef(transform->localScale.x, transform->localScale.y, transform->localScale.z);
}