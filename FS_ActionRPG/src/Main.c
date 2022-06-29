#include "FS_Engine.h"
#include "FS_Json.h"

typedef struct
{
	bool isInitialized;
	Arena *arena;

	Texture2D texture;
	GLuint textureID;
	Camera camera;

	TrueTypeFont font;

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
	Assets_LoadFont(&state->font, 20.0f, "resources/fonts/RobotoMono-Medium.ttf");
	OpenGL_AssignFontTexture(&state->font);

	Camera_CreateDefault(&state->camera, SCREEN_WIDTH, SCREEN_HEIGHT);

	const char *jsonString = "{ \"name\" : \"Julian\", \"age\" : 25.0, \"male\" : true, \"foods\" : [\"Pizza\", \"Burger\", { \"name\" : \"Johnny\" }] }";
	JsonValue *json = Json_Parse(state->arena, jsonString);

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

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, state->font.textureID);
	glScalef(10, 10, 10);
	OpenGL_DrawMesh(&state->quad);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 1, -1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1, 1, 1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	OpenGL_DrawText(&state->font, 0, 100, "Whatever");

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