#ifndef MYSTR_H
#define MYSTR_H
#include <stddef.h>

unsigned int sspn(const char* string, const char* reject);
int scmp(const char* p1, const char* p2);
char* stok(char* s, const char* ct);
unsigned int slen(const char* s);
char* scpy(char* destination, const char* src);

#endif
