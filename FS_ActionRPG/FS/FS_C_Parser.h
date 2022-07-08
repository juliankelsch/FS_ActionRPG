#ifndef __FS_C_PARSER_H__
#define __FS_C_PARSER_H__

#include <stdint.h>

// Gernereal questino of where to resolve complicated postfix / prefix operators and assignment operators
typedef enum
{
	TokenType_Unknown,

	TokenType_Identifier,
	TokenType_Keyword,

	// literals
	TokenType_String,
	TokenType_Float,
	TokenType_Integer,
	TokenType_Char,

	TokenType_OpenBracket,
	TokenType_CloseBracket,
	TokenType_OpenParen,
	TokenType_CloseParen,
	TokenType_OpenBrace,
	TokenType_CloseBrace,

	TokenType_Semicolon,
	TokenType_Colon,
	TokenType_QuestionMark,
	TokenType_Comma,

	TokenType_Plus,
	TokenType_Minus,
	TokenType_Divide,
	TokenType_Modulo,
	TokenType_Equals,

	TokenType_PlusPlus,
	TokenType_MinusMinus,

	TokenType_Asterisk, // Multiplication or dereference

	TokenType_Greater,
	TokenType_Less,

	TokenType_LogicalNot,
	TokenType_LogicalAnd,
	TokenType_LogicalOr,

	// Bitwise
	TokenType_BitwiseNot,
	TokenType_BitwiseAnd,
	TokenType_BitwiseOr,
	TokenType_BitwiseXor,

	TokenType_AddressOf,

	TokenType_ShiftRight,
	TokenType_ShiftLeft,

	TokenType_Dot,
	TokenType_Arrow,

	TokenType_PreprocessorDirective,

	TokenType_LineComment,
	TokenType_BlockComment,

	TokenType_EndOfStream
} TokenType;

typedef struct
{
	TokenType type;
	struct
	{
		char *at;
		uint32_t length;
	} string;
	uint32_t line;
} Token;

uint32_t CParser_Tokenize(const char *source, Token *tokenBuffer, uint32_t bufferCount);

#endif // __FS_C_PARSER_H__