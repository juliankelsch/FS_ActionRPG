#include "FS_Application.h"
#include "FS_Debug.h"
#include "FS_Input.h"

#include "GLFW//glfw3.h"

struct Application
{
	// Input
	TimeInfo timeInfo;
	Mouse mouse;
	Keyboard keyboard;
};

static Application _app = { 0 };

void GLFW_ErrorCallback(int error, const char *message)
{
	Debug_Error("GLFW Error %d -> %s", error, message);
}

void GLFW_ScrollCallback(GLFWwindow *window, double xOffset, double yOffset)
{
	Application *app = (Application*)glfwGetWindowUserPointer(window);
	app->mouse.scroll = (float)yOffset;
}

MouseButton GLFW_LookUpMouseButton(int glfwButton)
{
	switch (glfwButton)
	{
	case GLFW_MOUSE_BUTTON_LEFT:	return MouseButton_Left;
	case GLFW_MOUSE_BUTTON_RIGHT:	return MouseButton_Left;
	case GLFW_MOUSE_BUTTON_MIDDLE:	return MouseButton_Middle;
	}
	return MouseButton_Unknown;
}

Key GLFW_LookUpKey(int glfwKey)
{
	switch (glfwKey)
	{
	case GLFW_KEY_W: return Key_W;
	case GLFW_KEY_A: return Key_A;
	case GLFW_KEY_S: return Key_S;
	case GLFW_KEY_D: return Key_D;
	case GLFW_KEY_ESCAPE: return Key_Escape;
	case GLFW_KEY_SPACE: return Key_Space;

	case GLFW_KEY_0: return Key_0;
	case GLFW_KEY_1: return Key_1;
	case GLFW_KEY_2: return Key_2;
	case GLFW_KEY_3: return Key_3;
	case GLFW_KEY_4: return Key_4;
	case GLFW_KEY_5: return Key_5;
	case GLFW_KEY_6: return Key_6;
	case GLFW_KEY_7: return Key_7;
	case GLFW_KEY_8: return Key_8;
	case GLFW_KEY_9: return Key_9;

	case GLFW_KEY_F1: return Key_F1;
	case GLFW_KEY_F2: return Key_F2;
	case GLFW_KEY_F3: return Key_F3;
	case GLFW_KEY_F4: return Key_F4;
	case GLFW_KEY_F5: return Key_F5;
	case GLFW_KEY_F6: return Key_F6;
	case GLFW_KEY_F7: return Key_F7;
	case GLFW_KEY_F8: return Key_F8;
	case GLFW_KEY_F9: return Key_F9;
	case GLFW_KEY_F10: return Key_F10;
	case GLFW_KEY_F11: return Key_F11;
	case GLFW_KEY_F12: return Key_F12;
	}
	return Key_Unknown;
}

void GLFW_MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
	Application *app = (Application*)glfwGetWindowUserPointer(window);
	Mouse *mouse = Application_GetMouse(app);

	DigitalButton *mouseButton = mouse->buttons + GLFW_LookUpMouseButton(button);

	if (action == GLFW_PRESS)
	{
		mouseButton->isDown = true;
		mouseButton->transitionCount++;
	}
	else if (action == GLFW_RELEASE)
	{
		mouseButton->isDown = false;
		mouseButton->transitionCount++;
	}
}

void GLFW_KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	Application *app = (Application*)glfwGetWindowUserPointer(window);
	Keyboard *keyboard = &app->keyboard;

	DigitalButton *keyButton = keyboard->keys + GLFW_LookUpKey(key);

	if (action == GLFW_PRESS)
	{
		Debug_Log("Press");
		keyButton->isDown = true;
		keyButton->transitionCount++;
	}
	else if (action == GLFW_RELEASE)
	{
		Debug_Log("Release");
		keyButton->isDown = false;
		keyButton->transitionCount++;
	}
}

void ClearInput(Application *app)
{
	Mouse *mouse = &app->mouse;
	Keyboard *keyboard = &app->keyboard;
	mouse->scroll = 0.0f;

	for (size_t i = 0; i < MouseButton_Count; i++)
	{
		mouse->buttons[i].transitionCount = 0;
	}

	for (size_t i = 0; i < Key_Count; i++)
	{
		keyboard->keys[i].transitionCount = 0;
	}
}

void PreprocessEvents(Application *app)
{
	Keyboard *keyboard = &app->keyboard;
	Mouse *mouse = &app->mouse;
	TimeInfo *timeInfo = &app->timeInfo;

	for (size_t i = 0; i < MouseButton_Count; i++)
	{
		DigitalButton *button = mouse->buttons + i;
		if (WasReleasedThisFrame(*button))
		{
			button->downFor = 0.0f;
		}
		else if(WasHeldThisFrame(*button))
		{
			button->downFor += timeInfo->deltaTime;
		}
	}

	for (size_t i = 0; i < Key_Count; i++)
	{
		DigitalButton *button = keyboard->keys + i;
		if (WasReleasedThisFrame(*button))
		{
			button->downFor = 0.0f;
		}
		else if(WasHeldThisFrame(*button))
		{
			button->downFor += timeInfo->deltaTime;
		}
	}
}

void Application_Run(ApplicationSettings *settings)
{
	glfwSetErrorCallback(GLFW_ErrorCallback);

	if (!glfwInit())
	{
		Debug_Warn("GLFW library failed to initialize!");
		return;
	}

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	GLFWwindow *window = glfwCreateWindow(settings->windowSize.x, settings->windowSize.y, settings->windowTitle, 0, 0);

	if (!window)
	{
		Debug_Warn("GLFW failed to create window!");
		return;
	}

	glfwMakeContextCurrent(window);

	glfwSetWindowUserPointer(window, &_app);
	glfwSetMouseButtonCallback(window, GLFW_MouseButtonCallback);
	glfwSetKeyCallback(window, GLFW_KeyCallback);

	TimeInfo *timeInfo = &_app.timeInfo;
	Mouse *mouse = &_app.mouse;
	Keyboard *keyboard = &_app.keyboard;

	timeInfo->time = (float)glfwGetTime();


	bool isRunning = true;
	while (isRunning && !glfwWindowShouldClose(window))
	{
		ClearInput(&_app);
		glfwPollEvents();

		float oldTime = timeInfo->time;
		timeInfo->time = (float)glfwGetTime();
		timeInfo->deltaTime = timeInfo->time - oldTime;

		// Mouse position gets updated here instead of inside the GLFW cursor pos callback,
		// since the callback doesn't fire on mouse positions outside of the window content area.
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		Vector2 oldMouse = mouse->position;
		mouse->position = Vector2_Create((float)mouseX, (float)mouseY);
		mouse->motion = Vector2_Subtract(mouse->position, oldMouse);

		PreprocessEvents(&_app);

		if (settings->Update)
		{
			isRunning = settings->Update(settings->userData, &_app);
		}
		glfwSwapBuffers(window);
	}
}

Mouse *Application_GetMouse(Application *app)
{
	return &app->mouse;
}

Keyboard *Application_GetKeyboard(Application *app)
{
	return &app->keyboard;
}

TimeInfo *Application_GetTimeInfo(Application *app)
{
	return &app->timeInfo;
}
