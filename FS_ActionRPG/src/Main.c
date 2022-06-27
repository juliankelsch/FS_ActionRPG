#include "FS_Engine.h"

typedef struct
{
	Vector3 position;
	Quaternion rotation;
	Vector3 localScale;
} Transform;

typedef struct
{
	float x, y, width, height;
} Rect;

typedef struct
{
	int32_t x, y;
	int32_t width, height;
} RectInt;

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

typedef struct
{
	Vector3 position;
	Vector3 target;

	RectInt viewport;
	float fovy;
	float near, far;
} Camera;

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

typedef struct
{
	bool isInitialized;
	Arena *arena;

	Texture2D texture;
	GLuint textureID;
	Camera camera;

	Mesh quad;
	Mesh cube;
	Mesh plane;
	Mesh sphere;
	Mesh circle;
	Mesh cone;
	Mesh cylinder;
} State;

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;
static State state = { 0 };

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

void OpenGL_ApplyTransform(Transform *transform)
{
	glTranslatef(transform->position.x, transform->position.y, transform->position.z);
	glScalef(transform->localScale.x, transform->localScale.y, transform->localScale.z);
}

void State_Initialize(State *state)
{
	state->arena = Arena_Create(250 * 1000 * 1000);
	state->texture = Texture2D_CreateCircle(state->arena, 256, 0.0f, 1.0f);
	state->textureID = OpenGL_CreateTexture(&state->texture);

	state->quad = Mesh_CreateQuad(state->arena);
	state->cube = Mesh_CreateCube(state->arena);
	state->sphere = Mesh_CreateSphere(state->arena, 16, 32);
	state->plane = Mesh_CreatePlane(state->arena, (Vector3){1, 0, 0}, (Vector3){0, 0, 1}, 5);
	state->circle = Mesh_CreateCircle(state->arena, 0.5f, 32);
	state->cone = Mesh_CreateCone(state->arena, 1.0f, 0.5f, 32);
	state->cylinder = Mesh_CreateCylinder(state->arena, 1.0f, 0.5f, 32);

	Camera_CreateDefault(&state->camera, SCREEN_WIDTH, SCREEN_HEIGHT);
	state->isInitialized = true;
}

typedef enum
{
	PipelineFlag_Textured,
	PipelineFlag_ShowWireframe,
} PipelineFlag;

typedef struct
{
	uint32_t pipelineFlags;
} Material;

bool State_Update(void *userData, Application *app)
{
	State *state = (State *)userData;
	if (!state->isInitialized)
	{
		State_Initialize(state);
	}

	Mouse *mouse = Application_GetMouse(app);
	Keyboard *kb = Application_GetKeyboard(app);

	if (WasPressedThisFrame(kb->keys[Key_Escape]))
	{
		return false;
	}

	OpenGL_ApplyCamera(&state->camera);

	// clear
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// pipelineEnable
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// material
	glColor3f(1, 1, 1);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, state->textureID);


	glEnable(GL_CULL_FACE);
	if (WasHeldThisFrame(kb->keys[Key_Space]))
	{
		glCullFace(GL_FRONT);
	}
	else
	{
		glCullFace(GL_BACK);
	}

	Transform transform = { {0.0f, 0.0f, 0.0f}, { 1.0f, 1.0f, 1.0f } };
	//OpenGL_ApplyTransform(&transform);

	/*
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	OpenGL_DrawMesh(&state->quad);

	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	OpenGL_DrawMeshPoints(&state->plane);
	*/

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	OpenGL_DrawMesh_Colored(&state->cylinder, Color_Red);

	return true;
}

int main()
{

	ApplicationSettings settings = { 0 };

	// Configure window
	settings.windowSize.x = SCREEN_WIDTH;
	settings.windowSize.y = SCREEN_HEIGHT;
	settings.windowTitle = "Example Title";
	settings.userData = &state;

	// Setup update loop
	settings.Update = State_Update;

	Application_Run(&settings);
}