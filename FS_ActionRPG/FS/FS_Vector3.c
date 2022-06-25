#include "FS_Vector3.h"

Vector3 Vector3_Add(Vector3 a, Vector3 b)
{
	Vector3 result = {
		a.x + b.x, 
		a.y + b.y,
		a.z + b.z
	};
	return result;
}
