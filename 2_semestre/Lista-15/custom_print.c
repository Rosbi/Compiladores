#include<stdio.h>
#include"custom_print.h"

void myprint_first(const char *format, ...);
void my_next_print(const char *format, ...);

void (*myprintf)(const char *format, ...) = myprint_first;

void myprint_first(const char *format, ...){
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
	myprintf = my_next_print;
}
void my_next_print(const char *format, ...){
	va_list args;
	va_start(args, format);
	printf("\n");
	vprintf(format, args);
	va_end(args);
}