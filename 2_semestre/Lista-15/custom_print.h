#ifndef CUSTOM_PRINT_FUNCTION_H
#define CUSTOM_PRINT_FUNCTION_H

#include<stdarg.h>

extern void (*myprintf)(const char *format, ...);

#endif