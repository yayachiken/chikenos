#ifndef __STRING_H
#define __STRING_H

#include <stdint.h>

void *memset(void *s, int c, size_t n);

char *strcpy(char *dst, const char *src);

void *memcpy(void *dst, const void *src, size_t n);

#endif

