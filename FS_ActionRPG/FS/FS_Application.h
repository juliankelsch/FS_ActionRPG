#ifndef __FS_APPLICATION__
#define __FS_APPLICATION__

#include <stdbool.h>

#include "FS_Vector2.h"
#include "FS_Input.h"

typedef struct Application Application;

typedef bool UpdateFunc(void *userData, Application *app);

typedef struct
{
	vec2i windowSize;
	const char *windowTitle;

	void *userData;
	UpdateFunc *Update;
} ApplicationSettings;

void Application_Run(ApplicationSettings *settings);

vec2i Application_GetScreenSize(Application *app);
Mouse *Application_GetMouse(Application *app);
Keyboard *Application_GetKeyboard(Application *app);
TimeInfo *Application_GetTimeInfo(Application *app);

#endif // __FS_APPLICATION__
