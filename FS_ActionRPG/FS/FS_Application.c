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
	vec2i screen;
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
	case GLFW_MOUSE_BUTTON_RIGHT:	return MouseButton_Right;
	case GLFW_MOUSE_BUTTON_MIDDLE:	return MouseButton_Middle;
	}
	return MouseButton_Unknown;
}

Key GLFW_LookUpKey(int glfwKey)
{
	switch (glfwKey)
	{
	case GLFW_KEY_A: return Key_A;
	case GLFW_KEY_B: return Key_B;
	case GLFW_KEY_C: return Key_C;
	case GLFW_KEY_D: return Key_D;
	case GLFW_KEY_E: return Key_E;
	case GLFW_KEY_F: return Key_F;
	case GLFW_KEY_G: return Key_G;
	case GLFW_KEY_H: return Key_H;
	case GLFW_KEY_I: return Key_I;
	case GLFW_KEY_J: return Key_I;
	case GLFW_KEY_K: return Key_K;
	case GLFW_KEY_L: return Key_L;
	case GLFW_KEY_M: return Key_M;
	case GLFW_KEY_N: return Key_N;
	case GLFW_KEY_O: return Key_O;
	case GLFW_KEY_P: return Key_P;
	case GLFW_KEY_Q: return Key_Q;
	case GLFW_KEY_R: return Key_R;
	case GLFW_KEY_S: return Key_S;
	case GLFW_KEY_T: return Key_T;
	case GLFW_KEY_U: return Key_U;
	case GLFW_KEY_V: return Key_V;
	case GLFW_KEY_W: return Key_W;
	case GLFW_KEY_X: return Key_X;
	case GLFW_KEY_Y: return Key_Y;
	case GLFW_KEY_Z: return Key_Z;

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

	case GLFW_KEY_LEFT_SHIFT: return Key_LeftShift;
	case GLFW_KEY_RIGHT_SHIFT: return Key_RightShift;

	case GLFW_KEY_LEFT_CONTROL: return Key_LeftCtrl;
	case GLFW_KEY_RIGHT_CONTROL: return Key_RightCtrl;

	case GLFW_KEY_LEFT_ALT: return Key_LeftAlt;
	case GLFW_KEY_RIGHT_ALT: return Key_RightAlt;

	case GLFW_KEY_ESCAPE: return Key_Escape;
	case GLFW_KEY_SPACE: return Key_Space;
	case GLFW_KEY_ENTER: return Key_Enter;
	case GLFW_KEY_BACKSPACE: return Key_Backspace;
	case GLFW_KEY_TAB: return Key_Tab;
	case GLFW_KEY_CAPS_LOCK: return Key_Caps;

	//case GLFW_KEY_BACKSLASH: return Key_LeftBackslash;
	case GLFW_KEY_GRAVE_ACCENT: return Key_Backtick;

	case GLFW_KEY_COMMA: return Key_Comma;
	case GLFW_KEY_PERIOD: return Key_Dot;
	case GLFW_KEY_SLASH: return Key_Slash;
	case GLFW_KEY_BACKSLASH: return Key_RightBackslash;
	case GLFW_KEY_APOSTROPHE: return Key_Apostrophe;
	case GLFW_KEY_EQUAL: return Key_Equals;
	case GLFW_KEY_MINUS: return Key_Minus;
	case GLFW_KEY_SEMICOLON: return Key_Semicolon;
	case GLFW_KEY_LEFT_BRACKET: return Key_OpenBracket;
	case GLFW_KEY_RIGHT_BRACKET: return Key_CloseBracket;

	case GLFW_KEY_INSERT: return Key_Insert;
	case GLFW_KEY_DELETE: return Key_Delete;
	case GLFW_KEY_PAGE_UP: return Key_PageUp;
	case GLFW_KEY_PAGE_DOWN: return Key_PageDown;
	case GLFW_KEY_HOME: return Key_Home;
	case GLFW_KEY_END: return Key_End;

	case GLFW_KEY_PRINT_SCREEN: return Key_Print;
	case GLFW_KEY_SCROLL_LOCK: return Key_ScrollLock;
	case GLFW_KEY_PAUSE: return Key_Pause;

	case GLFW_KEY_KP_0: return Key_K0;
	case GLFW_KEY_KP_1: return Key_K1;
	case GLFW_KEY_KP_2: return Key_K2;
	case GLFW_KEY_KP_3: return Key_K3;
	case GLFW_KEY_KP_4: return Key_K4;
	case GLFW_KEY_KP_5: return Key_K5;
	case GLFW_KEY_KP_6: return Key_K6;
	case GLFW_KEY_KP_7: return Key_K7;
	case GLFW_KEY_KP_8: return Key_K8;
	case GLFW_KEY_KP_9: return Key_K9;
	case GLFW_KEY_KP_ENTER: return Key_KEnter;
	case GLFW_KEY_KP_ADD: return Key_KAdd;
	case GLFW_KEY_KP_SUBTRACT: return Key_KSubtract;
	case GLFW_KEY_KP_MULTIPLY: return Key_KMultiply;
	case GLFW_KEY_KP_DIVIDE: return Key_KDivide;
	case GLFW_KEY_NUM_LOCK: return Key_KNumLock;
	//case : return Key_KComma; // TODO? What is the real key for this?
	case GLFW_KEY_MENU: return Key_Menu;
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
	else if (action == GLFW_REPEAT)
	{
		mouseButton->isRepeat = true;
	}
}

void GLFW_KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	Application *app = (Application*)glfwGetWindowUserPointer(window);
	Keyboard *keyboard = &app->keyboard;

	DigitalButton *keyButton = keyboard->keys + GLFW_LookUpKey(key);

	if (action == GLFW_PRESS)
	{
		keyButton->isDown = true;
		keyButton->transitionCount++;
	}
	else if (action == GLFW_RELEASE)
	{
		keyButton->isDown = false;
		keyButton->transitionCount++;
	}
	else if (action == GLFW_REPEAT)
	{
		keyButton->isRepeat = true;
	}
}

void ClearInput(Application *app)
{
	Mouse *mouse = &app->mouse;
	Keyboard *keyboard = &app->keyboard;
	mouse->scroll = 0.0f;

	keyboard->inputCharCount = 0;

	for (size_t i = 0; i < MouseButton_Count; i++)
	{
		mouse->buttons[i].transitionCount = 0;
		mouse->buttons[i].isRepeat = false;
	}

	for (size_t i = 0; i < Key_Count; i++)
	{
		keyboard->keys[i].transitionCount = 0;
		keyboard->keys[i].isRepeat = false;
	}
}

void PostProcessEvents(Application *app)
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

void GLFW_CharCallback(GLFWwindow *window, unsigned int codepoint)
{
	Application *app = (Application*)glfwGetWindowUserPointer(window);
	Keyboard *keyboard = &app->keyboard;

	if (keyboard->inputCharCount < KEYBOARD_CHAR_QUEUE_LENGTH && codepoint < 128)
	{
		keyboard->inputChars[keyboard->inputCharCount++] = (char)codepoint;
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

	//glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
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
	glfwSetCharCallback(window, GLFW_CharCallback);

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
		vec2 oldMouse = mouse->position;
		mouse->position = vec2_create((float)mouseX, (float)mouseY);
		mouse->motion = vec2_subtract(mouse->position, oldMouse);

		glfwGetFramebufferSize(window, &_app.screen.x, &_app.screen.y);
		PostProcessEvents(&_app);

		if (settings->Update)
		{
			isRunning = settings->Update(settings->userData, &_app);
		}
		glfwSwapBuffers(window);
	}
}

vec2i Application_GetScreenSize(Application *app)
{
	return app->screen;
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
