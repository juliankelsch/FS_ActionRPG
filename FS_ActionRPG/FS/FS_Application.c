#include "FS_Application.h"
#include "FS_Debug.h"
#include "FS_Input.h"

#include "GLFW//glfw3.h"

struct Application
{
	// Input
	Time timeInfo;
	Mouse mouse;
	Keyboard keyboard;
};

void Application_Run(ApplicationSettings *settings)
{
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

	Application app = { 0 };
	glfwSetWindowUserPointer(window, &app);

	Time *timeInfo = &app.timeInfo;
	Mouse *mouse = &app.mouse;
	Keyboard *keyboard = &app.keyboard;

	timeInfo->time = (float)glfwGetTime();

	bool isRunning = true;
	while (isRunning && !glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		float oldTime = timeInfo->time;
		timeInfo->time = (float)glfwGetTime();
		timeInfo->deltaTime = timeInfo->time - oldTime;

		double cx, cy;
		glfwGetCursorPos(window, &cx, &cy);
		mouse->position.x = (float)cx;
		mouse->position.y = (float)cy;

		if (settings->Update)
		{
			isRunning = settings->Update(settings->userData, &app);
		}
		glfwSwapBuffers(window);
	}
}