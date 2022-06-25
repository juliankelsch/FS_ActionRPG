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

MouseButton GetMouseButton(int glfwButton)
{
	switch (glfwButton)
	{
	case GLFW_MOUSE_BUTTON_LEFT:	return MouseButton_Left;
	case GLFW_MOUSE_BUTTON_RIGHT:	return MouseButton_Left;
	case GLFW_MOUSE_BUTTON_MIDDLE:	return MouseButton_Middle;
	}
	return MouseButton_Unknown;
}

void GLFW_MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
	Application *app = (Application*)glfwGetWindowUserPointer(window);
	Mouse *mouse = Application_GetMouse(app);

	DigitalButton *mouseButton = mouse->buttons + GetMouseButton(button);

	bool isPressed = action == GLFW_PRESS;
	mouseButton->isDown = isPressed;
	mouseButton->transitionCount++;
}

void ClearInput(Application *app)
{
	Mouse *mouse = &app->mouse;
	mouse->scroll = 0.0f;

	for (size_t i = 0; i < MouseButton_Count; i++)
	{
		mouse->buttons[i].transitionCount = 0;
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
