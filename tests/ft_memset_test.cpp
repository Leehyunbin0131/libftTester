extern "C"
{
#define new tripouille
#include "libft.h"
#undef new
}

#include <unistd.h>
#include "sigsegv.hpp"
#include "check.hpp"
#include "leaks.hpp"
#include <string.h>

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_memset\t: ")

	char tab[100];

	/* Zero length must not write anything */
	memset(tab, 0, 100);
	ft_memset(tab, 'A', 0);
	/* 1 zero length untouched */ check(tab[0] == 0); showLeaks();

	/* Standard fill */
	ft_memset(tab, 'A', 42);
	int i = 0;
	for (; i < 100 && tab[i] == 'A'; ++i)
		;
	/* 2 fill 42 bytes only */ check(i == 42 && tab[42] == 0); showLeaks();

	/* Return value must equal first argument */
	memset(tab, 0, 100);
	void *r = ft_memset(tab, 'B', 10);
	/* 3 return value */ check(r == tab); showLeaks();

	/* Setting with 0 */
	memset(tab, 'A', 100);
	ft_memset(tab, 0, 100);
	int allZero = 1;
	for (int j = 0; j < 100; ++j)
		if (tab[j] != 0)
			allZero = 0;
	/* 4 set all to 0 */ check(allZero); showLeaks();

	/* Set with negative int (cast to unsigned char) */
	memset(tab, 0, 100);
	ft_memset(tab, -1, 5);
	/* 5 -1 cast = 0xFF */ check((unsigned char)tab[0] == 0xFF
		&& (unsigned char)tab[4] == 0xFF && tab[5] == 0); showLeaks();

	/* High int gets truncated to unsigned char */
	memset(tab, 0, 100);
	ft_memset(tab, 'A' + 256, 5);
	/* 6 256 truncation */ check(tab[0] == 'A' && tab[4] == 'A'); showLeaks();

	/* Single byte fill */
	memset(tab, 0, 100);
	ft_memset(tab, 'X', 1);
	/* 7 single byte */ check(tab[0] == 'X' && tab[1] == 0); showLeaks();

	/* Fill larger area */
	memset(tab, 0, 100);
	ft_memset(tab, 'Z', 100);
	int allZ = 1;
	for (int j = 0; j < 100; ++j)
		if (tab[j] != 'Z')
			allZ = 0;
	/* 8 fill 100 bytes */ check(allZ); showLeaks();

	/* Fill heap-allocated buffer */
	char *heap = (char *)malloc(50);
	ft_memset(heap, 'h', 50);
	int hh = 1;
	for (int j = 0; j < 50; ++j)
		if (heap[j] != 'h')
			hh = 0;
	/* 9 heap fill */ check(hh); free(heap); showLeaks();

	write(1, "\n", 1);
	return (0);
}
