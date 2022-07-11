#ifndef __FS_C_PARSER_H__
#define __FS_C_PARSER_H__

#include <stdint.h>

#include "FS_String.h"

typedef enum TokenType
{
	TokenType_Unknown,

	TokenType_Identifier,
	TokenType_Keyword,

	// literals
	TokenType_String,
	TokenType_Char,
	TokenType_Double,
	TokenType_Float,
	TokenType_Integer,
	TokenType_Long,

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

typedef struct Token
{
	TokenType type;
	String text;
} Token;

typedef struct Tokenizer
{
	const char *source;
	const char *at;
} Tokenizer;

Tokenizer Tokenizer_Create(const char *source);
void Token_PrintToken(Token token);
bool Token_Matches(Token token, TokenType type, const char *text);
Token Tokenizer_GetNextToken(Tokenizer *tok);
bool Tokenizer_AssumeToken(Tokenizer *tok, TokenType type, char *text);
bool Tokenizer_AssumeTokenType(Tokenizer *tok, TokenType type);

typedef enum SymbolType
{
	SymbolType_Unknown,

	SymbolType_BuiltInPrimitive,

	SymbolType_Struct,
	SymbolType_Union,
	SymbolType_Typedef,
	SymbolType_Function
} SymbolType;

typedef struct Declaration
{
	uint32_t symbolID;

	char *name;

	uint32_t pointerLevel;
	uint32_t arrayCount; // 0 if there is no array
} Declaration;

typedef struct StructInfo
{
	uint32_t symbolID;

	Declaration *members;
	uint32_t memberCount;
	uint32_t memberMax;
} StructInfo;

typedef struct FunctionInfo
{
	uint32_t symbolID;

	uint32_t returnID;

	Declaration *params;
	uint32_t paramCount;
	uint32_t paramMax;
} FunctionInfo;

typedef struct Symbol
{
	const char *name;
	SymbolType type;
} Symbol;

typedef struct SymbolData
{
	Symbol *symbols;
	uint32_t symbolCount;
	uint32_t symbolMax;

	StructInfo *structs;
	uint32_t structCount;
	uint32_t structMax;

	StructInfo *unions;
	uint32_t unionCount;
	uint32_t unionMax;

	FunctionInfo *functions;
	uint32_t functionCount;
	uint32_t functionMax;
} SymbolData;


void SymbolData_PushSymbol(SymbolData *data, char *name, size_t nameLength, SymbolType type);
void SymbolData_PushStructInfo(SymbolData *data, StructInfo info);
void SymbolData_PushFunctionInfo(SymbolData *data, FunctionInfo info);

#endif // __FS_C_PARSER_H__