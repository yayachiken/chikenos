#include <string.h>

void *memset(void *s, int c, size_t n)
{
	size_t i;
	for(i = 0; i < n; i++)
	{
		*((char*)s+i) = (unsigned char)c;
	}
	return s;
}

char *strcpy(char *dst, const char *src)
{
	while(*src)
	{
		*dst++ = *src++;
	}
	*dst = 0;
	return dst;
}

void *memcpy(void *dst, const void *src, size_t n)
{
	size_t i;
	for(i = 0; i < n; i++)
	{
		*((char*)dst+i) = *((const char*)src+i);
	}
	return dst;
}

