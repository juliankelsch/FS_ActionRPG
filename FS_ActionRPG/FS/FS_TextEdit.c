#include "FS_TextEdit.h"

void TextInput_Create(TextInput *input, Char *buffer, uint32_t bufferSize, uint32_t bufferUsed)
{
	input->string.chars = buffer;
	input->string.used = bufferUsed;
	input->string.size = bufferSize;
	input->cursor = bufferUsed;
}

void TextInput_OnChar(TextInput *input, Char c)
{
	if (StringBuffer_InsertCharAt(&input->string, input->cursor, c))
	{
		TextInput_MoveCursor(input, 1);
	}
}

void TextInput_OnPaste(TextInput *input, char *string)
{
	// TODO: firxpls,  horribly innefficient
	while (*string)
	{
		TextInput_OnChar(input, *string);
		string++;
	}
}

void TextInput_OnBackspace(TextInput *input)
{
	if (StringBuffer_RemoveCharAt(&input->string, input->cursor - 1))
	{
		TextInput_MoveCursor(input, -1);
	}
}

void TextInput_MoveCursor(TextInput *input, int32_t offset)
{
	input->cursor = (uint32_t)Math_Clamp((int32_t)input->cursor + offset, 0, input->string.used);
}

void TextInput_Clear(TextInput *input)
{
	input->cursor = 0;
	StringBuffer_Clear(&input->string);
}

String TextInput_GetString(TextInput *input)
{
	input->string.chars[input->string.used] = 0;
	return (String) { input->string.chars, input->string.used };
}