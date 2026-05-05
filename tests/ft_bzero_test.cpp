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
	title("ft_bzero\t: ")

	char tab[100];

	/* zero length must not write */
	memset(tab, 'A', 100);
	ft_bzero(tab, 0);
	/* 1 */ check(tab[0] == 'A'); showLeaks();

	/* zero first 42 bytes */
	ft_bzero(tab, 42);
	int i = 0;
	while (i < 100 && tab[i] == 0) {
		++i;
	}
	/* 2 */ check(i == 42 && tab[42] == 'A'); showLeaks();

	/* leading 0 should still be re-zeroed without affecting following */
	memset(tab, 'A', 100); tab[0] = 0;
	ft_bzero(tab, 42);
	i = 0;
	while (i < 100 && tab[i] == 0) {
		++i;
	}
	/* 3 */ check(i == 42); showLeaks();

	/* Whole buffer */
	memset(tab, 'X', 100);
	ft_bzero(tab, 100);
	int allZero = 1;
	for (int j = 0; j < 100; ++j)
		if (tab[j] != 0)
			allZero = 0;
	/* 4 zero entire buffer */ check(allZero); showLeaks();

	/* Single byte */
	memset(tab, 'B', 100);
	ft_bzero(tab, 1);
	/* 5 single byte */ check(tab[0] == 0 && tab[1] == 'B'); showLeaks();

	/* Heap buffer */
	char *heap = (char *)malloc(64);
	memset(heap, 'q', 64);
	ft_bzero(heap, 64);
	int hh = 1;
	for (int j = 0; j < 64; ++j)
		if (heap[j] != 0)
			hh = 0;
	/* 6 heap zero */ check(hh); free(heap); showLeaks();

	/* Compare with libc behavior (full match) */
	char a[64], b[64];
	memset(a, 'k', 64); memset(b, 'k', 64);
	ft_bzero(a, 32); bzero(b, 32);
	/* 7 matches libc bzero */ check(!memcmp(a, b, 64)); showLeaks();

	write(1, "\n", 1);
	return (0);
}
