#include "FS_Print.h"

#include <stdio.h>

int32_t Printf(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	int32_t returnCode = vprintf(format, args);
	va_end(args);

	return returnCode;
}