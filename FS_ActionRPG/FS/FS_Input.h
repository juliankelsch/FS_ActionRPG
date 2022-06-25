#ifndef __FS_INPUT_H__
#define __FS_INPUT_H__

#include <stdbool.h>

#include "FS_Vector2.h"

typedef struct
{
	bool isDown;				// Whether the button ended down.
	uint8_t transitionCount;	// How often the button transitioned from up to down between frames.
	float downFor;
} DigitalButton;

bool WasPressedThisFrame(DigitalButton button);
bool WasReleasedThisFrame(DigitalButton button);
bool WasHeldThisFrame(DigitalButton button);
bool WasHeldFor(DigitalButton button, float holdTime);

typedef struct
{
	float time;
	float deltaTime;
} TimeInfo;

typedef enum 
{
	MouseButton_Left,
	MouseButton_Right,
	MouseButton_Middle,

	MouseButton_Unknown,

	MouseButton_Count
} MouseButton;

typedef struct
{
	Vector2 position;
	Vector2 motion;

	float scroll;

	union
	{
		DigitalButton buttons[MouseButton_Count];
		struct
		{
			DigitalButton leftButton;
			DigitalButton rightButton;
			DigitalButton middleButton;
		};
	};
} Mouse;

typedef enum
{
	Key_W,
	Key_A,
	Key_S,
	Key_D,

	Key_Space,
	Key_Escape,
	Key_Return,

	Key_0,
	Key_1,
	Key_2,
	Key_3,
	Key_4,
	Key_5,
	Key_6,
	Key_7,
	Key_8,
	Key_9,

	Key_F1,
	Key_F2,
	Key_F3,
	Key_F4,
	Key_F5,
	Key_F6,
	Key_F7,
	Key_F8,
	Key_F9,
	Key_F10,
	Key_F11,
	Key_F12,

	Key_Unknown,

	Key_Count
} Key;

typedef struct
{
	union
	{
		DigitalButton keys[Key_Count];
		struct
		{
			DigitalButton keyW;
			DigitalButton keyA;
			DigitalButton keyS;
			DigitalButton keyD;
		};
	};
} Keyboard;

#endif // __FS_INPUT_H__