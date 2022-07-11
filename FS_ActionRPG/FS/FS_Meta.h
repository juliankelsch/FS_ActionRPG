#ifndef __FS_META_H__
#define __FS_META_H__

#include <stddef.h>
#include <stdint.h>

#define Meta_NameOf(T) #T
#define Meta_TypeOf(T) Type_##T

typedef enum Type Type;
typedef enum TypeKind TypeKind;
typedef struct Member Member;

struct Member
{
	Type type;
	uint8_t pointerLevel;
	const char *name;
	uint32_t offset;
};

enum TypeKind
{
	TypeKind_Primitive,
	TypeKind_Struct,
	TypeKind_Union,
	TypeKind_Enum,
	TypeKind_FuncPointer
};

enum Type
{
	Type_float,
	Type_double,
	Type_int,
	Type_uint32_t,
	Type_uint8_t,

	Type_Vector3,
	Type_Point3 = Type_Vector3,
	Type_Vector2,
	Type_Matrix4,
	Type_Person,
	Type_Entity,
	Type_GameState,

	Type_Fruit,
	Type_Vegetable,
	Type_Meat,
	Type_Color,
	Type_Direction,

	Type_Count,
};

extern Member Type_Vector3_Members[];

#endif // __FS_META_H__