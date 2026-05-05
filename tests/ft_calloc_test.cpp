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
#include <limits.h>
#include <stdint.h>

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_calloc\t: ")

	/* Standard allocation - 4 bytes zeroed */
	void *p = ft_calloc(2, 2);
	char e[] = {0, 0, 0, 0};
	/* 1 zeroed bytes */ check(!memcmp(p, e, 4));
	/* 2 size matches */ mcheck(p, 4); free(p); showLeaks();

	/* Overflow protection */
	/* 3 SIZE_MAX overflow */ check(ft_calloc(SIZE_MAX, SIZE_MAX) == NULL); showLeaks();

	/* @evportel - moulinette quirks */
	/* 4 INT_MAX*INT_MAX overflow */ check(ft_calloc(INT_MAX, INT_MAX) == NULL);
	/* 5 negative overflow */ check(ft_calloc(INT_MIN, INT_MIN) == NULL); showLeaks();

	/* Zero allocations - must not return NULL on most allocators */
	p = ft_calloc(0, 0);
	/* 6 calloc(0,0) */ check(p != NULL); free(p); showLeaks();
	p = ft_calloc(0, 5);
	/* 7 calloc(0,5) */ check(p != NULL); free(p); showLeaks();
	p = ft_calloc(5, 0);
	/* 8 calloc(5,0) */ check(p != NULL); free(p); showLeaks();
	/* 9 negative both */ check(ft_calloc(-5, -5) == NULL); showLeaks();
	p = ft_calloc(0, -5);
	/* 10 calloc(0,-5) */ check(p != NULL); free(p); showLeaks();
	p = ft_calloc(-5, 0);
	/* 11 calloc(-5,0) */ check(p != NULL); free(p); showLeaks();
	/* 12 calloc(3,-5) */ check(ft_calloc(3, -5) == NULL); showLeaks();
	/* 13 calloc(-5,3) */ check(ft_calloc(-5, 3) == NULL); showLeaks();

	/* Standard sized allocations - all bytes must be zero */
	p = ft_calloc(100, 1);
	int allZero = 1;
	for (int i = 0; i < 100; ++i)
		if (((char *)p)[i] != 0) allZero = 0;
	/* 14 all zeroed (100*1) */ check(allZero);
	/* 15 size match */ mcheck(p, 100); free(p); showLeaks();

	p = ft_calloc(10, sizeof(int));
	int allZero2 = 1;
	for (int i = 0; i < 10; ++i)
		if (((int *)p)[i] != 0) allZero2 = 0;
	/* 16 int array zeroed */ check(allZero2);
	/* 17 size match */ mcheck(p, 10 * sizeof(int)); free(p); showLeaks();

	/* Single element */
	p = ft_calloc(1, 1);
	/* 18 single byte */ check(p != NULL && ((char *)p)[0] == 0);
	/* 19 size match */ mcheck(p, 1); free(p); showLeaks();

	/* Large allocation */
	p = ft_calloc(1024, 1);
	int allZero3 = 1;
	for (int i = 0; i < 1024; ++i)
		if (((char *)p)[i] != 0) allZero3 = 0;
	/* 20 1KB zeroed */ check(allZero3); free(p); showLeaks();

	write(1, "\n", 1);
	return (0);
}
