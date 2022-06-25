#include "FS_Engine.h"

bool Game_Update(void *userData, Application *app)
{
	Mouse *mouse = Application_GetMouse(app);

	if (WasPressedThisFrame(mouse->leftButton))
	{
		return false;
	}

	Debug_Log("Mouse [%.1f, %.1f]", mouse->position.x, mouse->position.y);

	return true;
}

int main()
{
	ApplicationSettings settings = { 0 };

	// Configure window
	settings.windowSize.x = 1600;
	settings.windowSize.y = 900;
	settings.windowTitle = "Example Title";

	// Setup update loop
	settings.Update = Game_Update;

	Application_Run(&settings);
}