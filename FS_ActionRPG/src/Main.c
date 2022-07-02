#define FS_OPENGL_1_0
#include "FS_Engine.h"

// Planned
// 
// Profiler
// GUI
// Commandline
// Entitysystem
// Sound system
// Particle system
// Modern GL
// Asset ssytem
// Skinned Animations
// Threads

// 2D Renderer for images
// 3D Renderer for (textured/colored quads and meshes, skinned meshes)


typedef struct
{
	Vector3 position;

	float moveSpeed;
	Vector3 moveDir;

	float height;
	float radius;

	Mesh *mesh;
} Player;

typedef struct
{
	bool isInitialized;
	Arena *arena;

	Keyboard *keyboard;
	Mouse *mouse;
	TimeInfo *timeInfo;

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

	Mesh playerMesh;
	Mesh groundMesh;

	bool hit;
	RayHitInfo hitInfo;

	FontFamily fontFamily;
	TextStyle textStyle;
	RenderList2D renderList;

	Player player;
} Game;

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;

static Game game = { 0 };

void Game_Initialize(Game *game)
{
	game->arena = Arena_Create(250 * 1000 * 1000);
	game->texture = Texture2D_CreateCircle(game->arena, 256, 0.0f, 1.0f);
	game->textureID = OpenGL_CreateTexture(&game->texture);

	game->quad = Mesh_CreateQuad(game->arena);
	game->cube = Mesh_CreateCube(game->arena);
	game->sphere = Mesh_CreateSphere(game->arena, 16, 32);
	game->plane = Mesh_CreatePlane(game->arena, (Vector3){1, 0, 0}, (Vector3){0, 0, 1}, 10.0f, 5);
	game->circle = Mesh_CreateCircle(game->arena, 0.5f, 32);
	game->cone = Mesh_CreateCone(game->arena, 1.0f, 0.5f, 32);
	game->cylinder = Mesh_CreateCylinder(game->arena, 1.0f, 0.5f, 32);
	Assets_LoadFont(&game->font, 20.0f, "resources/fonts/RobotoMono-Medium.ttf");
	OpenGL_AssignFontTexture(&game->font);

	Assets_LoadFontFamily(&game->fontFamily, 25.0f, 
		"resources/fonts/RobotoMono-Medium.ttf",
		"resources/fonts/RobotoMono-Bold.ttf",
		"resources/fonts/RobotoMono-MediumItalic.ttf",
		"resources/fonts/RobotoMono-BoldItalic.ttf"
	);

	/*
	Assets_LoadFontFamily(&game->fontFamily, 25.0f, 
		"resources/fonts/SourceCodePro-Medium.ttf",
		"resources/fonts/SourceCodePro-Bold.ttf",
		"resources/fonts/SourceCodePro-MediumItalic.ttf",
		"resources/fonts/SourceCodePro-BoldItalic.ttf"
	);
	*/

	for (size_t i = 0; i < FontStyle_Count; i++)
	{
		OpenGL_AssignFontTexture(game->fontFamily.fonts + i);
	}

	GUI_TextStyle_CreateDefault(&game->textStyle);

	RenderList2D_Init(&game->renderList, game->arena, (Rect) {0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT}, 1000, 5000, 20000);

	Camera_CreateDefault(&game->camera, SCREEN_WIDTH, SCREEN_HEIGHT);
	/*
	const char *jsonString = "{ \"name\" : \"Julian\", \"age\" : 25.0, \"male\" : true, \"foods\" : [\"Pizza\", \"Burger\", { \"name\" : \"Johnny\" }] }";
	JsonValue *json = Json_Parse(state->arena, jsonString);
	*/

	Player *player = &game->player;

	player->position = Vector3_Zero;
	player->height = 1.8f;
	player->radius = 0.25f;
	player->moveSpeed = 8.0f;

	game->playerMesh = Mesh_CreateCylinder(game->arena, player->height, player->radius, 16);
	game->groundMesh = Mesh_CreatePlane(game->arena, Vector3_X, Vector3_Z, 100.0f, 9);
	for (int i = 0; i < game->groundMesh.vertexCount; i++)
	{
		game->groundMesh.vertices[i].position.y = (Mathf_Random01() - 0.5f) * 10;
	}


	player->mesh = &game->playerMesh;

	game->isInitialized = true;
}

void DrawVector3(TrueTypeFont *font, float x, float y, const char *name, Vector3 vector)
{
	OpenGL_DrawText(font, 0, 100, "%s [%.2f, %.2f, %.2f]", name , vector.x, vector.y, vector.z);
}

void RenderUI(Game *game)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 1, -1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1, 1, 1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//OpenGL_DrawText(&game->font, 0, 100, "Player position [%.2f, %.2f, %.2f]", game->player.position.x, game->player.position.y, game->player.position.z);

	RenderList2D *list = &game->renderList;
	Rect bounds = { 0, 0, 400, SCREEN_HEIGHT};

	//RenderList2D_SetBounds(list, bounds);
	RenderList2D_DrawRect(list, bounds, Color_Hex(0x000000BB));

	float inset = -10;
	RectOffsets textInset = {inset, inset, inset, inset};
	Rect textBounds = Rect_GetOffsetRect(bounds, textInset);

	//RenderList2D_SetBounds(list, textBounds);

	Vector2 pos = {textBounds.x, textBounds.y};
	game->textStyle.colorMode = ColorMode_Normal;
	game->textStyle.overflow = OverflowMode_Ignore;
	game->textStyle.alignment.vertical = VAlignment_Center;
	game->textStyle.alignment.horizontal = HAlignment_Center;
	game->textStyle.color = Color_White;
	game->textStyle.bold = false;
	game->textStyle.italic = true;
	game->textStyle.lineSpacing = 1.0f;
	game->textStyle.characterSpacing = 1.0f;
	game->textStyle.textCase = TextCase_Normal;
	RenderList2D_DrawText(&game->renderList, &game->fontFamily, pos, textBounds, &game->textStyle, "This is some centered poem\nThis is some centered poem\nThis is some centered poem\nThis is some centered poem\nThis is some centered poem\n");

	game->textStyle.colorMode = ColorMode_Gradient;
	game->textStyle.gradientColors[Corner_TopLeft] = Color_Green;
	game->textStyle.gradientColors[Corner_TopRight] = Color_Green;
	game->textStyle.gradientColors[Corner_BotLeft] = Color_Cyan;
	game->textStyle.gradientColors[Corner_BotRight] = Color_Cyan;
	game->textStyle.alignment.vertical = VAlignment_Top;
	game->textStyle.alignment.horizontal = HAlignment_Center;
	game->textStyle.bold = true;
	game->textStyle.italic = true;
	game->textStyle.textCase = TextCase_Upper;
	game->textStyle.characterSpacing = 1.4f;
	RenderList2D_DrawText(&game->renderList, &game->fontFamily, pos, textBounds, &game->textStyle, "Editor");

	//DrawVector3(&game->font, 0, 20, "Player position", game->player.position);
	OpenGL_DrawList(&game->renderList, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Game_Simulate(Game *game)
{
	Player *player = &game->player;
	Keyboard *keyboard = game->keyboard;
	Mouse *mouse = game->mouse;
	TimeInfo *timeInfo = game->timeInfo;

	game->camera.position = (Vector3){0.0f, 15.0f, 10.0f};

	Vector2 movementInput = { 0.0f, 0.0f };
	if (keyboard->keyW.isDown) movementInput.y -= 1.0f;
	if (keyboard->keyS.isDown) movementInput.y += 1.0f;
	if (keyboard->keyA.isDown) movementInput.x -= 1.0f;
	if (keyboard->keyD.isDown) movementInput.x += 1.0f;
	movementInput = Vector2_NormalizedSafe(movementInput);

	player->moveDir = (Vector3){movementInput.x, 0.0f, movementInput.y};
	Vector3 velocity = Vector3_Multiply_F(player->moveDir, player->moveSpeed * timeInfo->deltaTime);
	player->position = Vector3_Add(player->position, velocity);

	float halfBounds = 50.0f;
	if (player->position.x + player->radius > halfBounds)
	{
		player->position.x = halfBounds - player->radius;
	}
	else if (player->position.x - player->radius < -halfBounds)
	{
		player->position.x = player->radius - halfBounds;
	}

	if (player->position.z + player->radius > halfBounds)
	{
		player->position.z = halfBounds - player->radius;
	}
	else if (player->position.z - player->radius < -halfBounds)
	{
		player->position.z = player->radius - halfBounds;
	}

	RayHitInfo groundHit = { 0 };

	if (Ray3_GetClosestMeshIntersection(Vector3_Add(player->position, Vector3_Up), Vector3_Down, &game->groundMesh, &groundHit))
	{
		game->hit = true;
		game->hitInfo = groundHit;
		player->position.y = groundHit.point.y;
	}
	else
	{
		game->hit = false;
	}
}

bool Game_Update(void *userData, Application *app)
{
	Game *game = (Game *)userData;
	if (!game->isInitialized)
	{
		Game_Initialize(game);
	}

	Mouse *mouse = Application_GetMouse(app);
	Keyboard *kb = Application_GetKeyboard(app);
	TimeInfo *timeInfo = Application_GetTimeInfo(app);

	game->keyboard = kb;
	game->mouse = mouse;
	game->timeInfo = timeInfo;

	if (WasPressedThisFrame(kb->keys[Key_Escape]))
	{
		return false;
	}

	Game_Simulate(game);

	OpenGL_ApplyCamera(&game->camera);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	glDisable(GL_SCISSOR_TEST);
	glScissor(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(game->player.position.x, game->player.position.y, game->player.position.z);
	OpenGL_DrawMesh_Colored(&game->playerMesh, Color_Red);
	glPopMatrix();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	OpenGL_DrawMesh_Colored(&game->groundMesh, Color_Hex(0x444444FF));

	if (game->hit)
	{
		while (glGetError() != GL_NO_ERROR)
		{
			printf("ogl error");
		}
		glPushMatrix();
		glTranslatef(game->hitInfo.point.x, game->hitInfo.point.y, game->hitInfo.point.z);
		OpenGL_DrawMesh_Colored(&game->sphere, Color_Green);
		glPopMatrix();
	}

	RenderUI(game);
	RenderList2D_Clear(&game->renderList);
	return true;
}

int main()
{

	ApplicationSettings settings = { 0 };

	// Configure window
	settings.windowSize.x = SCREEN_WIDTH;
	settings.windowSize.y = SCREEN_HEIGHT;
	settings.windowTitle = "Example Title";
	settings.userData = &game;

	// Setup update loop
	settings.Update = Game_Update;

	Application_Run(&settings);
}