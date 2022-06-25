#include "FS_Engine.h"

bool Game_Update(void *userData, Application *app)
{
	Mouse *mouse = Application_GetMouse(app);
	Keyboard *kb = Application_GetKeyboard(app);

	if (WasPressedThisFrame(kb->keys[Key_Escape]))
	{
		return false;
	}

	if (WasHeldFor(kb->keyW, 2.0f))
	{
		return false;
	}

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