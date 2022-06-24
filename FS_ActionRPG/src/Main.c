#include <stdio.h>
#include <GLFW/glfw3.h>

#include "FS_Debug.h"
#include "FS_Arena.h"

int main()
{
	if (!glfwInit())
	{
		Debug_Warn("GLFW library failed to initialize!");
		return;
	}

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	GLFWwindow *window = glfwCreateWindow(1600, 900, "ActionRPG", 0, 0);

	if (!window)
	{
		Debug_Warn("GLFW failed to create window!");
		return;
	}

	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glfwSwapBuffers(window);
	}
}