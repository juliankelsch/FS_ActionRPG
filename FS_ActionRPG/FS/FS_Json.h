#ifndef __FS_JSON_H__
#define  __FS_JSON_H__

#include "FS_Arena.h"

#include <stdint.h>
#include <stdbool.h>

// The JSON standard doesn't distinguish between integers and floats.
typedef enum 
{
	JsonValueType_Integer,
	JsonValueType_Float,
	JsonValueType_Boolean,
	JsonValueType_String,
	JsonValueType_Array,
	JsonValueType_Object
} JsonValueType;

typedef struct JsonAttribute JsonAttribute;
typedef struct JsonObject JsonObject;
typedef struct JsonArray JsonArray;
typedef struct JsonValue JsonValue;

struct JsonAttribute
{
	char *key;
	JsonValue *value;
};

struct JsonObject
{
	uint32_t attributeCount;
	JsonAttribute *attributes;
};

struct JsonArray
{
	uint32_t count;
	JsonValue **values;
};

struct JsonValue
{
	JsonValueType type;
	union
	{
		double float64;
		int64_t integer64;
		bool boolean;
		char *string;
		JsonArray *array;
		JsonObject *object;
	};
};

// Parses a json string 'string' and stores the resulting data structure inside the given memory arena 'arena'.
// Also stores all additional data needed for parsing - like the token stream - inside the arena.
JsonValue *Json_Parse(Arena *arena, const char *string);

#endif // __FS_JSON_H__