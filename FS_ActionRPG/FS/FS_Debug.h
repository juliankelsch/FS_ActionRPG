#pragma once

#include <stdarg.h>
#include <stdio.h>
#include <assert.h>

#define Debug_Assert assert

#define Debug_Log(format, ...) (printf("Debug [LOG] <%s:%d>:", __FILE__, __LINE__), printf(format, __VA_ARGS__), putchar('\n'))
#define Debug_Warn(format, ...) (printf("Debug [WARN] <%s:%d>:", __FILE__, __LINE__), printf(format, __VA_ARGS__), putchar('\n'))
#define Debug_Error(format, ...) (printf("Debug [ERROR] <%s:%d>:", __FILE__, __LINE__), printf(format, __VA_ARGS__), putchar('\n'))

