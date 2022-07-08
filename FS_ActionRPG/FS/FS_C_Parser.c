#include "FS_C_Parser.h"

typedef struct
{
	Token *tokens;
	uint32_t maxTokens;
	uint32_t tokenCount;

	const char * source;
	const char *at;
	uint32_t line;
} Tokenizer;

void Tokenizer_ParseNextToken(Tokenizer *tok)
{

}

void Tokenizer_Run(Tokenizer *tok)
{
	while (*tok->at && tok->tokenCount < tok->maxTokens)
	{
		Tokenizer_ParseNextToken(tok);
	}
}

uint32_t CParser_Tokenize(const char *source, Token *tokenBuffer, uint32_t bufferCount)
{
	Tokenizer tokenizer = { 0 };
	tokenizer.tokens = tokenBuffer;
	tokenizer.source = source;
	tokenizer.at = source;
	tokenizer.maxTokens = bufferCount;

	Tokenizer_Run(&tokenizer);
}
