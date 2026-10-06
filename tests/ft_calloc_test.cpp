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
#include <stdint.h>

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_calloc\t: ")

	/* Standard allocation - 4 bytes zeroed */
	void *p = ft_calloc(2, 2);
	char e[] = {0, 0, 0, 0};
	/* 1 zeroed bytes */ check(p && !memcmp(p, e, 4));
	/* 2 capacity */ mcheck(p, 4); free(p); showLeaks();

	/* The requested array cannot fit in size_t; wrapped allocations are invalid. */
	p = ft_calloc(SIZE_MAX, SIZE_MAX);
	/* 3 overflow wrapping to 1 */ check(p == NULL); free(p); showLeaks();
	p = ft_calloc(SIZE_MAX / 2 + 1, 2);
	/* 4 overflow wrapping to 0 */ check(p == NULL); free(p); showLeaks();
	p = ft_calloc(2, SIZE_MAX / 2 + 1);
	/* 5 reversed overflow operands */ check(p == NULL); free(p); showLeaks();

	/* C 7.22.3 permits NULL or a freeable pointer for zero-size allocations.
	   Do not dereference the result or require a particular allocator policy. */
	p = ft_calloc(0, 0);
	/* 6 calloc(0,0) */ mcheck(p, 0); free(p); showLeaks();
	p = ft_calloc(0, 5);
	/* 7 calloc(0,5) */ mcheck(p, 0); free(p); showLeaks();
	p = ft_calloc(5, 0);
	/* 8 calloc(5,0) */ mcheck(p, 0); free(p); showLeaks();

	/* Standard sized allocations - all bytes must be zero */
	p = ft_calloc(100, 1);
	int allZero = p != NULL;
	for (int i = 0; p && i < 100; ++i)
		if (((char *)p)[i] != 0) allZero = 0;
	/* 9 all zeroed (100*1) */ check(allZero);
	/* 10 capacity */ mcheck(p, 100); free(p); showLeaks();

	p = ft_calloc(10, sizeof(int));
	int allZero2 = p != NULL;
	for (int i = 0; p && i < 10; ++i)
		if (((int *)p)[i] != 0) allZero2 = 0;
	/* 11 int array zeroed */ check(allZero2);
	/* 12 capacity */ mcheck(p, 10 * sizeof(int)); free(p); showLeaks();

	/* Single element */
	p = ft_calloc(1, 1);
	/* 13 single byte */ check(p != NULL && ((char *)p)[0] == 0);
	/* 14 capacity */ mcheck(p, 1); free(p); showLeaks();

	/* Large allocation */
	p = ft_calloc(1024, 1);
	int allZero3 = p != NULL;
	for (int i = 0; p && i < 1024; ++i)
		if (((char *)p)[i] != 0) allZero3 = 0;
	/* 15 1KB zeroed */ check(allZero3); free(p); showLeaks();

	write(1, "\n", 1);
	return (0);
}
