#include "FS_Application.h"
#include "FS_Debug.h"
#include "FS_Arena.h"

#include <stdbool.h>

bool Game_Update(void *userData, Application *app)
{
	Debug_Log("Frame");
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