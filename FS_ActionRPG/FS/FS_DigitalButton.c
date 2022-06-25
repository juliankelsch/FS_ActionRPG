#include "FS_Input.h"

bool WasPressedThisFrame(DigitalButton button)
{
	return (button.isDown + button.transitionCount) > 1;
}

bool WasReleasedThisFrame(DigitalButton button)
{
	return (!button.isDown + button.transitionCount) > 1;
}

bool WasHeldThisFrame(DigitalButton button)
{
	return button.isDown && button.transitionCount == 0;
}

bool WasHeldFor(DigitalButton button, float holdTime)
{
	return button.downFor >= holdTime;
}
