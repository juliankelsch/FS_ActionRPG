#include "FS_C_Parser.h"

#include "FS_String.h"

Tokenizer Tokenizer_Create(const char *source)
{
	Tokenizer tok = { 0 };
	tok.source = source;
	tok.at = source;
	return tok;
}

#include <stdio.h>

static const char *TokenTypeToString(TokenType type)
{
	switch (type)
	{
	case TokenType_Unknown: return "TokenType_Unknown";
	case TokenType_Identifier: return "TokenType_Identifier";
	case TokenType_Keyword: return "TokenType_Keyword";
	case TokenType_String: return "TokenType_String";
	case TokenType_Char: return "TokenType_Char";
	case TokenType_Double: return "TokenType_Double";
	case TokenType_Float: return "TokenType_Float";
	case TokenType_Integer: return "TokenType_Integer";
	case TokenType_Long: return "TokenType_Long";
	case TokenType_OpenBracket: return "TokenType_OpenBracket";
	case TokenType_CloseBracket: return "TokenType_CloseBracket";
	case TokenType_OpenParen: return "TokenType_OpenParen";
	case TokenType_CloseParen: return "TokenType_CloseParen";
	case TokenType_OpenBrace: return "TokenType_OpenBrace";
	case TokenType_CloseBrace: return "TokenType_CloseBrace";
	case TokenType_Semicolon: return "TokenType_Semicolon";
	case TokenType_Colon: return "TokenType_Colon";
	case TokenType_QuestionMark: return "TokenType_QuestionMark";
	case TokenType_Comma: return "TokenType_Comma";
	case TokenType_Plus: return "TokenType_Plus";
	case TokenType_Minus: return "TokenType_Minus";
	case TokenType_Divide: return "TokenType_Divide";
	case TokenType_Modulo: return "TokenType_Modulo";
	case TokenType_Equals: return "TokenType_Equals";
	case TokenType_PlusPlus: return "TokenType_PlusPlus";
	case TokenType_MinusMinus: return "TokenType_MinusMinus";
	case TokenType_Asterisk: return "TokenType_Asterisk";
	case TokenType_Greater: return "TokenType_Greater";
	case TokenType_Less: return "TokenType_Less";
	case TokenType_LogicalNot: return "TokenType_LogicalNot";
	case TokenType_LogicalAnd: return "TokenType_LogicalAnd";
	case TokenType_LogicalOr: return "TokenType_LogicalOr";
	case TokenType_BitwiseNot: return "TokenType_BitwiseNot";
	case TokenType_BitwiseAnd: return "TokenType_BitwiseAnd";
	case TokenType_BitwiseOr: return "TokenType_BitwiseOr";
	case TokenType_BitwiseXor: return "TokenType_BitwiseXor";
	case TokenType_AddressOf: return "TokenType_AddressOf";
	case TokenType_ShiftRight: return "TokenType_ShiftRight";
	case TokenType_ShiftLeft: return "TokenType_ShiftLeft";
	case TokenType_Dot: return "TokenType_Dot";
	case TokenType_Arrow: return "TokenType_Arrow";
	case TokenType_PreprocessorDirective: return "TokenType_PreprocessorDirective";
	case TokenType_LineComment: return "TokenType_LineComment";
	case TokenType_BlockComment: return "TokenType_BlockComment";
	case TokenType_EndOfStream: return "TokenType_EndOfStream";
	default: return "";
	}
}

void Token_PrintToken(Token token)
{
	printf("[%s] %.*s\n", TokenTypeToString(token.type), token.text.length, token.text.chars);
}

bool Token_Matches(Token token, TokenType type, const char *text)
{
	return token.type == type && String_Matches(token.text, text);
}

static Token Tokenizer_ParseIdentifier(Tokenizer *tok)
{
	const char *start = tok->at;
	while (Char_IsIdentifier(*tok->at))
	{
		tok->at++;
	}
	return (Token) { TokenType_Identifier, { start, tok->at - start } };
}

static Token Tokenizer_ParseString(Tokenizer *tok)
{
	const char *start = tok->at;
	while (*tok->at)
	{
		tok->at++;
		if (*tok->at == '\"')
		{
			tok->at++;
			break;
		}
	}
	return (Token) { TokenType_String, { start, tok->at - start } };
}

static Token Tokenizer_SingleCharToken(Tokenizer *tok, TokenType type)
{
	Token token = { type, {tok->at ,1} };
	tok->at++;
	return token;
}

/*
	TokenType_Keyword,

	TokenType_Char,
	TokenType_Double,
	TokenType_Float,
	TokenType_Integer,
	TokenType_Long,

	TokenType_Plus, // can be plus plus
	TokenType_Minus, // can be arrow
	TokenType_Divide, // cna be comment

	TokenType_PlusPlus,
	TokenType_MinusMinus,

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
*/

static Token Tokenizer_ParseNumber(Tokenizer *tok)
{
	tok->at++;
	return (Token) { TokenType_Unknown, { tok->at - 1, 1 } };
}

static Token Tokenizer_ParseChar(Tokenizer *tok)
{
	const char *start = tok->at;
	while (*tok->at)
	{
		tok->at++;
		if (*tok->at == '\'')
		{
			tok->at++;
			break;
		}
	}
	return (Token) { TokenType_Char, { start, tok->at - start } };
}

static Token Tokenizer_ParseLineComment(Tokenizer *tok)
{
	const char *start = tok->at;
	while (*tok->at)
	{
		tok->at++;
		if (*tok->at == '\n')
		{
			tok->at++;
			break;
		}
	}
	return (Token) { TokenType_LineComment, { start, tok->at - start } };
}

static Token Tokenizer_ParseBlockComment(Tokenizer *tok)
{
	const char *start = tok->at;
	tok->at++;
	tok->at++;
	while (*tok->at)
	{
		tok->at++;
		if (tok->at[0] == '*' && tok->at[1] == '/')
		{
			tok->at++;
			tok->at++;
			break;
		}
	}
	return (Token) { TokenType_BlockComment, { start, tok->at - start } };
}

// division OR line comment OR Multiline comment
static Token Tokenizer_ParseSlash(Tokenizer *tok)
{
	if (tok->at[1] == '/')
	{
		return Tokenizer_ParseLineComment(tok);
	}
	else if (tok->at[1] == '*')
	{
		return Tokenizer_ParseBlockComment(tok);
	}
	else
	{
		return Tokenizer_SingleCharToken(tok, TokenType_Divide);
	}
}

Token Tokenizer_GetNextToken(Tokenizer *tok)
{
	tok->at = String_SkipWhitespace(tok->at);
	if (Char_IsAlpha(*tok->at) || *tok->at == '_')
		return Tokenizer_ParseIdentifier(tok);
	else if (Char_IsDigit(*tok->at) || (*tok->at == '.' && Char_IsDigit(tok->at[1])))
		return Tokenizer_ParseNumber(tok);
	else if (*tok->at == '\"')
		return Tokenizer_ParseString(tok);
	else if (*tok->at == '\'')
		return Tokenizer_ParseChar(tok);
	else if (*tok->at == '/')
		return Tokenizer_ParseSlash(tok);
	else if(*tok->at == '#')
		return Tokenizer_SingleCharToken(tok, TokenType_PreprocessorDirective);
	else if(*tok->at == '(')
		return Tokenizer_SingleCharToken(tok, TokenType_OpenParen);
	else if(*tok->at == ')')
		return Tokenizer_SingleCharToken(tok, TokenType_CloseParen);
	else if(*tok->at == '{')
		return Tokenizer_SingleCharToken(tok, TokenType_OpenBrace);
	else if(*tok->at == '}')
		return Tokenizer_SingleCharToken(tok, TokenType_CloseBrace);
	else if(*tok->at == '[')
		return Tokenizer_SingleCharToken(tok, TokenType_OpenBracket);
	else if(*tok->at == ']')
		return Tokenizer_SingleCharToken(tok, TokenType_CloseBracket);
	else if(*tok->at == ';')
		return Tokenizer_SingleCharToken(tok, TokenType_Semicolon);
	else if(*tok->at == ':')
		return Tokenizer_SingleCharToken(tok, TokenType_Colon);
	else if(*tok->at == '?')
		return Tokenizer_SingleCharToken(tok, TokenType_QuestionMark);
	else if(*tok->at == ',')
		return Tokenizer_SingleCharToken(tok, TokenType_Comma);
	else if(*tok->at == '%')
		return Tokenizer_SingleCharToken(tok, TokenType_Modulo);
	else if(*tok->at == '=')
		return Tokenizer_SingleCharToken(tok, TokenType_Equals);
	else if(*tok->at == '*')
		return Tokenizer_SingleCharToken(tok, TokenType_Asterisk);
	else if(*tok->at == '<')
		return Tokenizer_SingleCharToken(tok, TokenType_Less); // TODO can be shift left
	else if(*tok->at == '>')
		return Tokenizer_SingleCharToken(tok, TokenType_Greater); // TODO: can be shift right
	else if(*tok->at == '^')
		return Tokenizer_SingleCharToken(tok, TokenType_BitwiseXor);
	else if (*tok->at)
		return Tokenizer_SingleCharToken(tok, TokenType_Unknown);
	else
		return (Token) { TokenType_EndOfStream };
}

bool Tokenizer_AssumeToken(Tokenizer *tok, TokenType type, char *text)
{
	Token token = Tokenizer_GetNextToken(tok);
	return Token_Matches(token, type, text);
}

bool Tokenizer_AssumeTokenType(Tokenizer *tok, TokenType type)
{
	Token token = Tokenizer_GetNextToken(tok);
	return token.type == type;
}
