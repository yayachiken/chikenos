#ifndef _LIBC_STDDEF_H
#define _LIBC_STDDEF_H

/*
 * stddef.h header file
 */

#undef NULL
#if defined(__cplusplus)
#define NULL 0
#else
#define NULL ((void *)0)
#endif

#endif
