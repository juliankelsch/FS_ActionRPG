#include "FS_Engine.h"

#include <math.h>

float Mathf_Lerp(float a, float b, float t)
{
	return (1.0f - t) * a + t * b;
}

float Mathf_Sqrt(float x)
{
	return sqrtf(x);
}

float Mathf_Clamp(float x, float low, float high)
{
	return x < low ? low : (x > high ? high : x);
}

float Mathf_Clamp01(float x)
{
	return Mathf_Clamp(x, 0.0f, 1.0f);
}

float Mathf_MapToRange(float x, float fromLow, float fromHigh, float toLow, float toHigh)
{
	float percent = (x - fromLow) / (fromHigh - fromLow);
	return Mathf_Lerp(toLow, toHigh, percent);
}

typedef struct
{
	Vector3 position;
	Vector3 localScale;
} Transform;

typedef struct
{
	Vector3 position;
	Vector3 normal;
	Vector2 texCoords;
	Color color;
} Vertex;

typedef struct
{
	uint32_t vertexCount;
	uint32_t indexCount;

	Vertex *vertices;
	uint32_t *indices;
} Mesh;

Mesh Mesh_CreateQuad(Arena *arena)
{
	Mesh quad = { 0 };

	quad.vertexCount = 4;
	quad.indexCount = 6;
	quad.vertices = Arena_PushArray(arena, quad.vertexCount, Vertex);
	quad.indices =	Arena_PushArray(arena, quad.indexCount, uint32_t);

	Vector3 normal = { 0, 0, 1 };
	Color color = { 255, 255, 255, 255 };

	quad.vertices[0] = (Vertex){ {-0.5f, 0.5f}, normal, {0.0f, 1.0f}, color };
	quad.vertices[1] = (Vertex){ {0.5f, 0.5f}, normal, {1.0f, 1.0f}, color };
	quad.vertices[2] = (Vertex){ {-0.5f, -0.5f}, normal, { 0.0f, 0.0f }, color};
	quad.vertices[3] = (Vertex){ {0.5f, -0.5f}, normal, { 1.0f, 0.0f }, color};

	quad.indices[0] = 0;
	quad.indices[1] = 2;
	quad.indices[2] = 1;

	quad.indices[3] = 1;
	quad.indices[4] = 2;
	quad.indices[5] = 3;

	return quad;
}

typedef struct
{
	bool isInitialized;
	Arena *arena;
	Texture2D texture;
	GLuint textureID;
	Mesh quad;
} State;

typedef struct
{
	int32_t x, y;
	int32_t width, height;
} RectangleInt;

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;
static State state = { 0 };


Texture2D Texture2D_Create(Arena *arena, uint16_t width, uint16_t height)
{
	Texture2D result = { 
		width, height, 
		Arena_PushArray(arena, width * height, Color)
	};
	return result;
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

Texture2D Texture2D_CreateCircle(Arena *arena, uint16_t size, float innerRadius, float outerRadius)
{
	Texture2D texture = { size, size, Arena_PushArray(arena, size * size, Color) };

	Color transparent = { 0, 0, 0, 0 };
	Color white = { 255, 255, 255, 255 };
	Color red = { 255, 0, 0, 255};

	float inner = innerRadius * 0.5f;
	float outer = outerRadius * 0.5f;
	
	for (size_t i = 0; i < texture.height; i++)
	{
		for (size_t j = 0; j < texture.width; j++)
		{
			float s = (float)j / (texture.width - 1);
			float t = (float)i / (texture.height - 1);

			float dist = Mathf_Sqrt((s - 0.5f) * (s - 0.5f) + (t - 0.5f) * (t - 0.5f));

			Color *pixel = texture.pixels + (i * texture.width + j);
			if (dist <= outer)
			{
				if (dist <= inner)
				{
					*pixel = white;
				}
				else
				{
					float alpha = Mathf_MapToRange(dist, inner, outer, 1.0f, 0.0f);
					Color mixed = { 255, 255, 255, alpha * 255 };
					*pixel = mixed;
				}
			}
			else
			{
				*pixel = transparent;
			}
		}
	}

	return texture;
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

void OpenGL_ApplyTransform(Transform *transform)
{
	glTranslatef(transform->position.x, transform->position.y, transform->position.z);
	glScalef(transform->localScale.x, transform->localScale.y, transform->localScale.z);
}

void State_Initialize(State *state)
{
	state->arena = Arena_Create(250 * 1000 * 1000);
	state->texture = Texture2D_CreateCircle(state->arena, 256, 0.95f, 1.0f);
	state->textureID = OpenGL_CreateTexture(&state->texture);
	state->quad = Mesh_CreateQuad(state->arena);
	state->isInitialized = true;
}


bool Game_Update(void *userData, Application *app)
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

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glColor3f(1.0f, 1.0f, 1.0f);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float aspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	glOrtho(-aspect, aspect, -1, 1, 1, -1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture(GL_TEXTURE_2D, state->textureID);

	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);

	Transform transform = { {0.0f, 1.0f, 0.0f}, { 1.0f, 0.5f, 1.0f } };
	OpenGL_ApplyTransform(&transform);
	OpenGL_DrawMesh(&state->quad);

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
	settings.Update = Game_Update;

	Application_Run(&settings);
}