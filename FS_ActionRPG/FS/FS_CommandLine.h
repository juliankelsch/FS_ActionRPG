#ifndef  __FS_COMMANDLINE_H__
#define  __FS_COMMANDLINE_H__

#include <stdint.h>
#include <FS_Macros.h>

typedef enum
{
	ArgType_None,

	ArgType_String,
	ArgType_Int,
	ArgType_Float
} ArgType;

typedef struct
{
	ArgType arg;
	union
	{
		char *string;
		int32_t int32;
		float float32;
	};
} Arg;

#define COMMAND_MAX_ARGS 8

typedef struct CMD CMD;

typedef void CommandCallback(CMD *cmd, Arg *args, void *userData);

typedef struct
{
	const char *name;
	CommandCallback *callback;
	ArgType args[COMMAND_MAX_ARGS];

} Command;

struct CMD
{
	Command *commands;
	void *userData;
};

/*
void CMD_Create(CMD *cmd, uint32_t commandCount, Command *commands);

void Command_setpos(CMD *cmd, Arg *args, void *userData)
{
	Entity *selectedEntity = (Game *)userData->selectedEntity;

	selectedEntity->pos = (Vector3){ args[0].float32, args[1].float32, args[2].float32 };
}

void Command_reset(CMD *cmd, Arg *args, void *userArgs)
{
	Entity *selectedEntity = (Game *)userArgs->selectedEntity;

	selectedEntity->pos = Vector3_Zero;
}

void Command_print_hello(CMD *cmd, Arg *args, void *userData)
{
	printf(args[0].string);
}

void Tesetsadf()
{
	CMD cmd;
	Command commands[] = {
		{"setpos", Command_setpos, {ArgType_Float, ArgType_Float, ArgType_Float}},
		{"reset", Command_reset},
		{"print", Command_print_hello, {ArgType_String}},
	};
	CMD_Create(&cmd, ArrayCount(commands), commands);
}
*/


#endif // __FS_COMMANDLINE_H__
