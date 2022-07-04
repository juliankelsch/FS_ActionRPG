#include "FS_Json.h"
#include "FS_Debug.h"

#include <stdlib.h>
#include <string.h>

#define JSON_MAX_TOKENS 5000

typedef enum 
{
	// tokens with values
	JsonTokenType_Integer,
	JsonTokenType_Float,
	JsonTokenType_Boolean,
	JsonTokenType_String,

	// single char tokens
	JsonTokenType_CurlyBraceOpen,
	JsonTokenType_CurlyBraceClose,
	JsonTokenType_BracketOpen,
	JsonTokenType_BracketClose,
	JsonTokenType_Comma,
	JsonTokenType_Colon,

	JsonTokenType_End,
} JsonTokenType;

typedef struct 
{
	JsonTokenType type;
	union
	{
		int64_t integer64;
		double float64;
		bool boolean;
		char *string;
	};
} JsonToken;

typedef struct
{
	Arena *arena;
	JsonToken tokens[JSON_MAX_TOKENS];
	uint32_t tokenCount;

	char *json;
	char* at;
} JsonLexer;

bool IsDigit(char c)
{
	return c >= '0' && c <= '9';
}

bool IsWhitespace(char c)
{
	return c == '\n' || c == '\r' || c == ' ' || c == '\t';
}

bool NumberContainsDot(char *string)
{
	while (IsDigit(*string++))
	{
		if (*string == '.')
		{
			return true;
		}
	}
	return false;
}

JsonTokenType DetermineNumberType(char *string)
{
	return NumberContainsDot(string) ? JsonTokenType_Float : JsonTokenType_Integer;
}

void JsonLexer_AddToken(JsonLexer *lexer, JsonToken token)
{
	if (lexer->tokenCount < JSON_MAX_TOKENS)
	{
		lexer->tokens[lexer->tokenCount++] = token;
	}
	else
	{
		Debug_Warn("JsonLexer error: tokenCount reached limit of JSON_MAX_TOKENS(%d)", JSON_MAX_TOKENS);
	}
}

void JsonLexer_ParseNumber(JsonLexer *lexer)
{
	JsonTokenType numberType = DetermineNumberType(lexer->at);
	JsonToken token = { numberType };
	if (numberType == JsonValueType_Integer)
	{
		token.integer64 = strtoll(lexer->at, &lexer->at, 0);
	}
	else if (numberType == JsonTokenType_Float)
	{
		token.float64 = strtod(lexer->at, &lexer->at);
	}
	JsonLexer_AddToken(lexer, token);
}

void JsonLexer_AddBooleanToken(JsonLexer *lexer, bool value)
{
	JsonToken token = { JsonTokenType_Boolean };
	token.boolean = value;
	lexer->at += value ? 4 : 5;
	JsonLexer_AddToken(lexer, token);
}

void JsonLexer_SkipWhitespace(JsonLexer *lexer)
{
	while (IsWhitespace(*lexer->at))
	{
		lexer->at++;
	}
}

void JsonLexer_ParseString(JsonLexer *lexer)
{
	lexer->at++;
	char *start = lexer->at;
	while (*lexer->at && *lexer->at != '\"')
	{
		lexer->at++;
	}

	if (*lexer->at == '\"')
	{
		uint32_t strlen = lexer->at - start;
		JsonToken token = { JsonTokenType_String };
		token.string = Arena_PushArray(lexer->arena, strlen + 1, char);
		strncpy(token.string, start, strlen);
		token.string[strlen] = '\0';
		JsonLexer_AddToken(lexer, token);
		lexer->at++;
	}
}

void JsonLexer_AddSingleCharToken(JsonLexer *lexer, JsonTokenType type)
{
	JsonToken token = { type };
	JsonLexer_AddToken(lexer, token);
	lexer->at++;
}

JsonToken *Json_Tokenize(Arena *arena, const char *string)
{
	JsonLexer *lexer = Arena_Push(arena, JsonLexer);
	lexer->arena = arena;
	lexer->json = string;
	lexer->at = lexer->json;

	while (*lexer->at)
	{
		JsonLexer_SkipWhitespace(lexer);

		if (IsDigit(*lexer->at))
		{
			JsonLexer_ParseNumber(lexer);
		}
		else if (lexer->at[0] == 't'
			&& lexer->at[1] == 'r'
			&& lexer->at[2] == 'u'
			&& lexer->at[3] == 'e')
		{
			JsonLexer_AddBooleanToken(lexer, true);
		}
		else if (lexer->at[0] == 'f'
			&& lexer->at[1] == 'a'
			&& lexer->at[2] == 'l'
			&& lexer->at[3] == 's'
			&& lexer->at[4] == 'e')
		{
			JsonLexer_AddBooleanToken(lexer, false);
		}
		else if (*lexer->at == '\"')
		{
			JsonLexer_ParseString(lexer);
		}
		else if (*lexer->at == '{')
		{
			JsonLexer_AddSingleCharToken(lexer, JsonTokenType_CurlyBraceOpen);
		}
		else if (*lexer->at == '}')
		{
			JsonLexer_AddSingleCharToken(lexer, JsonTokenType_CurlyBraceClose);
		}
		else if (*lexer->at == '[')
		{
			JsonLexer_AddSingleCharToken(lexer, JsonTokenType_BracketOpen);
		}
		else if (*lexer->at == ']')
		{
			JsonLexer_AddSingleCharToken(lexer, JsonTokenType_BracketClose);
		}
		else if (*lexer->at == ':')
		{
			JsonLexer_AddSingleCharToken(lexer, JsonTokenType_Colon);
		}
		else if (*lexer->at == ',')
		{
			JsonLexer_AddSingleCharToken(lexer, JsonTokenType_Comma);
		}
		else
		{
			Debug_Warn("JsonLexer -> Unexpected character '%c'", *lexer->at);
			break;
		}
	}
	JsonLexer_AddSingleCharToken(lexer, JsonTokenType_End);
	return lexer->tokens;
}

typedef struct
{
	Arena *arena;
	JsonToken *at;
} JsonParser;

JsonValue *JsonParser_ParseValue(JsonParser *parser);

uint32_t JsonParser_GetTokenCountInCurrentScope(JsonParser *parser, JsonTokenType type)
{
	uint32_t tokenCount = 0;
	uint32_t scope = 0;

	JsonToken *at = parser->at;
	while (scope >= 0 && at->type != JsonTokenType_End)
	{
		if (at->type == type && scope == 0)
		{
			tokenCount++;
		}
		
		scope += at->type == JsonTokenType_BracketOpen || at->type == JsonTokenType_CurlyBraceOpen;
		scope -= at->type == JsonTokenType_BracketClose || at->type == JsonTokenType_CurlyBraceClose;
		at++;
	}

	return tokenCount;
}

uint32_t JsonParser_GetAttributeCount(JsonParser *parser)
{
	return JsonParser_GetTokenCountInCurrentScope(parser, JsonTokenType_Colon);
}

JsonObject *JsonParser_ParseObject(JsonParser *parser)
{
	Debug_Assert(parser->at->type == JsonTokenType_CurlyBraceOpen);
	parser->at++;

	JsonObject *object = Arena_Push(parser->arena, JsonObject);
	// TODO peek attribute count
	object->attributeCount = 0;
	object->attributes = Arena_PushArray(parser->arena, 
		JsonParser_GetTokenCountInCurrentScope(parser, JsonTokenType_Colon), 
		JsonAttribute);

	JsonAttribute *attribute = object->attributes;
	while (parser->at->type != JsonTokenType_CurlyBraceClose)
	{
		if (parser->at->type == JsonTokenType_End)
		{
			Debug_Error("JsonParser -> Unexpected end of token stream while parsing Json object!");
			break;
		}

		// expect key
		if (parser->at->type != JsonTokenType_String)
		{
			// error
			break;
		}
		attribute->key = parser->at->string;
		parser->at++;

		// expect colon
		if (parser->at->type != JsonTokenType_Colon)
		{
			// error
			break;
		}
		parser->at++;

		// expect value
		attribute->value = JsonParser_ParseValue(parser);
		if (!attribute->value)
		{
			// error
			break;
		}
		object->attributeCount++;

		// expect comma
		if (parser->at->type == JsonTokenType_Comma)
		{
			parser->at++;
			attribute++;
		}
	}
	return object;
}

JsonArray *JsonParser_ParseArray(JsonParser *parser)
{
	Debug_Assert(parser->at->type == JsonTokenType_BracketOpen);
	parser->at++;

	JsonArray *array = Arena_Push(parser->arena, JsonArray);

	array->count = 0;
	array->values = Arena_PushArray(parser->arena, JsonParser_GetTokenCountInCurrentScope(parser, JsonTokenType_Comma) + 1, JsonValue *);

	JsonValue **value = array->values;
	while (parser->at->type != JsonTokenType_BracketClose)
	{
		if (parser->at->type == JsonTokenType_End)
		{
			Debug_Error("JsonParser -> Unexpected end of token stream while parsing json array!");
			return NULL;
		}

		// expect value
		*value = JsonParser_ParseValue(parser);
		if (!*value)
		{
			// error
			break;
		}
		array->count++;

		// expect comma
		if (parser->at->type == JsonTokenType_Comma)
		{
			value++;
			parser->at++;
		}
	}
	return array;
}

JsonValue *JsonParser_ParseValue(JsonParser *parser)
{
	JsonValue *value = Arena_Push(parser->arena, JsonValue);
	if (parser->at->type == JsonTokenType_Integer)
	{
		value->type = JsonValueType_Integer;
		value->integer64 = parser->at->integer64;
	}
	else if (parser->at->type == JsonTokenType_Float)
	{
		value->type = JsonValueType_Float;
		value->float64 = parser->at->float64;
	}
	else if (parser->at->type == JsonTokenType_Boolean)
	{
		value->type = JsonValueType_Boolean;
		value->boolean = parser->at->boolean;
	}
	else if (parser->at->type == JsonTokenType_String)
	{
		value->type = JsonValueType_String;
		value->string = parser->at->string;
	}
	else if (parser->at->type == JsonTokenType_CurlyBraceOpen)
	{
		value->type = JsonValueType_Object;
		value->object = JsonParser_ParseObject(parser);
	}
	else if (parser->at->type == JsonTokenType_BracketOpen)
	{
		value->type = JsonValueType_Array;
		value->array = JsonParser_ParseArray(parser);
	}
	else
	{
		Debug_Error("JsonParser -> Unexpected token.");
	}
	parser->at++;
	return value;
}

JsonValue *Json_ParseTokens(Arena *arena, JsonToken *tokens)
{
	JsonParser parser = { 0 };
	parser.arena = arena;
	parser.at = tokens;

	return JsonParser_ParseValue(&parser);
}

void PrintJson(JsonValue *value);

void PrintObject(JsonObject *object)
{
	printf("{\n");
	for (size_t i = 0; i < object->attributeCount - 1; i++)
	{
		printf("\"%s\" : ", object->attributes[i].key);
		PrintJson(object->attributes[i].value);
		printf(",\n");
	}
	printf("\"%s\" : ", object->attributes[object->attributeCount - 1].key);
	PrintJson(object->attributes[object->attributeCount - 1].value);
	printf("\n}\n");
}

void PrintArray(JsonArray *array)
{
	printf("[");
	for (size_t i = 0; i < array->count - 1; i++)
	{
		PrintJson(array->values[i]);
		printf(", ");
	}
	PrintJson(array->values[array->count - 1]);
	printf("]");
}

void PrintJson(JsonValue *value)
{
	switch (value->type)
	{
	case JsonValueType_Integer: printf("%llu", value->integer64); break;
	case JsonValueType_Float: printf("%.2f", value->float64); break;
	case JsonValueType_Boolean: printf("\"%s\"", value->boolean ? "true" : "false"); break;
	case JsonValueType_String: printf("%s", value->string); break;
	case JsonValueType_Object: PrintObject(value->object); break;
	case JsonValueType_Array: PrintArray(value->array); break;
	}

}

JsonValue *Json_Parse(Arena *arena, const char *string)
{
	JsonToken *tokens = Json_Tokenize(arena, string);
	JsonValue *result = Json_ParseTokens(arena, tokens);
	//PrintJson(result);
	return result;
}