#include <string.h>

void *memset(void *s, int c, size_t n)
{
	int i;
	for(i = 0; i < n; i++)
	{
		*(s+i) = (unsigned char)c;
	}
}

char *strcpy(char *restrict dst, const char *restrict src)
{
	while(*src)
	{
		*dst++ = *src++
	}
	*dst = 0;
}

void *memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	int i;
	for(i = 0; i < n; i++)
	{
		*(dst+i) = *(src+i);
	}
}

