#ifndef __FS_INPUT_H__
#define __FS_INPUT_H__

#include <stdbool.h>

#include "FS_Vector2.h"

typedef struct
{
	bool isDown;				// Whether the button ended down.
	uint8_t transitionCount;	// How often the button transitioned from up to down between frames.
} DigitalButton;

bool WasPressedThisFrame(DigitalButton button);
bool WasReleasedThisFrame(DigitalButton button);
bool WasHeldThisFrame(DigitalButton button);

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

typedef struct
{
	bool dummy;
} Keyboard;

#endif // __FS_INPUT_H__