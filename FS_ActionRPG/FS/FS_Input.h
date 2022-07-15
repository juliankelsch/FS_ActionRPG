#ifndef __FS_INPUT_H__
#define __FS_INPUT_H__

#include <stdbool.h>

#include "FS_Vector2.h"

typedef struct
{
	bool isDown;				// Whether the button ended down.
	bool isRepeat;
	uint8_t transitionCount;	// How often the button transitioned from up to down between frames.
	float downFor;
} DigitalButton;

bool WasPressedThisFrame(DigitalButton button);
bool WasReleasedThisFrame(DigitalButton button);
bool WasRepeatedThisFrame(DigitalButton button);
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
	vec2 position;
	vec2 motion;

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
	Key_A,
	Key_B,
	Key_C,
	Key_D,
	Key_E,
	Key_F,
	Key_G,
	Key_H,
	Key_I,
	Key_J,
	Key_K,
	Key_L,
	Key_M,
	Key_N,
	Key_O,
	Key_P,
	Key_Q,
	Key_R,
	Key_S,
	Key_T,
	Key_U,
	Key_V,
	Key_W,
	Key_X,
	Key_Y,
	Key_Z,


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

	Key_LeftShift,
	Key_RightShift,

	Key_LeftCtrl,
	Key_RightCtrl,

	Key_LeftAlt,
	Key_RightAlt,

	Key_Space,
	Key_Escape,
	Key_Enter,
	Key_Backspace,
	Key_Tab,
	Key_Caps,

	Key_LeftBackslash,
	Key_Backtick,

	Key_Comma, 
	Key_Dot, 
	Key_Slash, 
	Key_RightBackslash, 
	Key_Apostrophe, 
	Key_Equals,
	Key_Minus,
	Key_Semicolon,
	Key_OpenBracket, 
	Key_CloseBracket, 

	Key_Insert,
	Key_Delete,
	Key_PageUp,
	Key_PageDown,
	Key_Home,
	Key_End,

	Key_Print,
	Key_ScrollLock,
	Key_Pause,

	Key_K0,
	Key_K1,
	Key_K2,
	Key_K3,
	Key_K4,
	Key_K5,
	Key_K6,
	Key_K7,
	Key_K8,
	Key_K9,
	Key_KEnter,
	Key_KAdd,
	Key_KSubtract,
	Key_KMultiply,
	Key_KDivide,
	Key_KNumLock,
	Key_KComma,

	Key_Menu,

	Key_Unknown,

	Key_Count
} Key;

#define KEYBOARD_CHAR_QUEUE_LENGTH 128
typedef struct
{
	char inputChars[KEYBOARD_CHAR_QUEUE_LENGTH];
	uint32_t inputCharCount;

	union
	{
		DigitalButton keys[Key_Count];
		struct
		{
			DigitalButton a;
			DigitalButton b;
			DigitalButton c;
			DigitalButton d;
			DigitalButton e;
			DigitalButton f;
			DigitalButton g;
			DigitalButton h;
			DigitalButton i;
			DigitalButton k;
			DigitalButton j;
			DigitalButton l;
			DigitalButton m;
			DigitalButton n;
			DigitalButton o;
			DigitalButton p;
			DigitalButton q;
			DigitalButton r;
			DigitalButton s;
			DigitalButton t;
			DigitalButton u;
			DigitalButton v;
			DigitalButton w;
			DigitalButton x;
			DigitalButton y;
			DigitalButton z;

			DigitalButton num[10];
			DigitalButton fKey[12];
			
			DigitalButton leftShift;
			DigitalButton rightShift;

			DigitalButton leftCtrl;
			DigitalButton rightCtrl;

			DigitalButton leftAlt;
			DigitalButton rightAlt;

			DigitalButton space;
			DigitalButton esc;
			DigitalButton backspace;
			DigitalButton enter;
			DigitalButton tab;
			DigitalButton caps;

			DigitalButton leftBackslash;
			DigitalButton backtic;

			DigitalButton comma;
			DigitalButton dot;
			DigitalButton slash;
			DigitalButton rightBackslash;
			DigitalButton apostrophe;
			DigitalButton equals;
			DigitalButton minus;
			DigitalButton semicolon;
			DigitalButton openBracket;
			DigitalButton closeBracket;

			DigitalButton insert;
			DigitalButton delete;
			DigitalButton pageUp;
			DigitalButton pageDown;
			DigitalButton home;
			DigitalButton end;

			DigitalButton print;
			DigitalButton scrollLock;
			DigitalButton pause;

			// numpad / keypad
			DigitalButton k0;
			DigitalButton k1;
			DigitalButton k2;
			DigitalButton k3;
			DigitalButton k4;
			DigitalButton k5;
			DigitalButton k6;
			DigitalButton k7;
			DigitalButton k8;
			DigitalButton k9;
			DigitalButton kEnter;
			DigitalButton kAdd;
			DigitalButton kSubtract;
			DigitalButton kMultiply;
			DigitalButton kDivide;
			DigitalButton kNumLock;
			DigitalButton kComma;

			DigitalButton menu;
		};
	};
} Keyboard;

typedef struct
{
	Keyboard *keyboard;
	Mouse *mouse;
	TimeInfo *timeInfo;
} Input;

#endif // __FS_INPUT_H__