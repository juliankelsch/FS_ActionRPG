#ifndef __FS_TEXTEDIT_H__
#define __FS_TEXTEDIT_H__

#include "FS_String.h"
#include "FS_Mathf.h"

// Extremely simple text input widget
typedef struct
{
	StringBuffer string;
	uint32_t cursor;
} TextInput;

void TextInput_Create(TextInput *input, Char *buffer, uint32_t bufferSize, uint32_t bufferUsed);
void TextInput_OnChar(TextInput *input, Char c);
void TextInput_OnPaste(TextInput *input, char *string);
void TextInput_OnBackspace(TextInput *input);
void TextInput_MoveCursor(TextInput *input, int32_t offset);
void TextInput_Clear(TextInput *input);
String TextInput_GetString(TextInput *input);

#endif // __FS_TEXTEDIT_H__
