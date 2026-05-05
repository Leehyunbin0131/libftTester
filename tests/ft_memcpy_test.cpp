extern "C"
{
#define new tripouille
#include "libft.h"
#undef new
}

#include "sigsegv.hpp"
#include "check.hpp"
#include "leaks.hpp"
#include <string.h>

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_memcpy\t: ")

	char dest[100];

	/* Zero length must not write */
	memset(dest, 'A', 100);
	ft_memcpy(dest, "coucou", 0);
	/* 1 zero len no write */ check(dest[0] == 'A'); showLeaks();

	/* Zero length with NULL allowed (n == 0) */
	char *rtn = (char *)ft_memcpy(dest, NULL, 0);
	/* 2 NULL allowed when n=0 */ check(rtn == dest && dest[0] == 'A'); showLeaks();

	/* Copy bytes including null bytes */
	char src[] = {0, 0};
	ft_memcpy(dest, src, 2);
	int i = 0;
	for (; i < 100 && dest[i] == 0; ++i)
		;
	/* 3 copies bytes including nulls */ check(i == 2 && dest[2] == 'A'); showLeaks();

	/* Standard copy of a normal string */
	memset(dest, 'A', 100);
	rtn = (char *)ft_memcpy(dest, "Hello", 5);
	/* 4 return is dest */ check(rtn == dest); showLeaks();
	/* 5 content match */ check(!memcmp(dest, "Hello", 5) && dest[5] == 'A'); showLeaks();

	/* Binary data with high bytes */
	unsigned char src2[] = {0xFF, 0x00, 0x7F, 0x80, 0x42};
	unsigned char buf[10]; memset(buf, 0xAA, 10);
	ft_memcpy(buf, src2, 5);
	/* 6 binary copy */ check(!memcmp(buf, src2, 5) && buf[5] == 0xAA); showLeaks();

	/* Compare with libc memcpy - exact behavior */
	char a[50], b[50];
	memset(a, 0, 50); memset(b, 0, 50);
	ft_memcpy(a, "Tripouille is here!", 19);
	memcpy(b, "Tripouille is here!", 19);
	/* 7 matches libc */ check(!memcmp(a, b, 50)); showLeaks();

	/* Larger copy */
	char big_src[1000], big_dst[1000];
	for (int j = 0; j < 1000; ++j) big_src[j] = (char)(j % 256);
	memset(big_dst, 0, 1000);
	ft_memcpy(big_dst, big_src, 1000);
	/* 8 1KB copy */ check(!memcmp(big_dst, big_src, 1000)); showLeaks();

	/* Heap buffers */
	char *hsrc = strdup("data 42!");
	char *hdst = (char *)malloc(strlen(hsrc) + 1);
	ft_memcpy(hdst, hsrc, strlen(hsrc) + 1);
	/* 9 heap copy */ check(!strcmp(hsrc, hdst)); free(hsrc); free(hdst); showLeaks();

	/* Single byte copy */
	memset(dest, 'A', 100);
	ft_memcpy(dest, "Z", 1);
	/* 10 single byte */ check(dest[0] == 'Z' && dest[1] == 'A'); showLeaks();

	write(1, "\n", 1);
	return (0);
}
