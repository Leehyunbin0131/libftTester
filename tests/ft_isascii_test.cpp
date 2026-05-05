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
#include <ctype.h>
#include <climits>

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_isascii\t: ")

	/* Boundary cases - ASCII range is [0, 127] */
	/* 1 */ check(!ft_isascii(-1)); showLeaks();
	/* 2 */ check(ft_isascii(0)); showLeaks();
	/* 3 */ check(!ft_isascii(128)); showLeaks();
	/* 4 */ check(ft_isascii(127)); showLeaks();

	/* All values in [0,127] must be ASCII */
	int ok = 1;
	for (int c = 0; c < 128; ++c)
		if (!ft_isascii(c))
			ok = 0;
	/* 5 every value in [0,127] is ascii */ check(ok); showLeaks();

	/* All values in [128, 255] must NOT be ASCII */
	ok = 1;
	for (int c = 128; c < 256; ++c)
		if (ft_isascii(c))
			ok = 0;
	/* 6 every value in [128,255] is not ascii */ check(ok); showLeaks();

	/* Negative and large values */
	/* 7 */ check(!ft_isascii(-2)); showLeaks();
	/* 8 */ check(!ft_isascii(-128)); showLeaks();
	/* 9 */ check(!ft_isascii(255)); showLeaks();
	/* 10 */ check(!ft_isascii(256)); showLeaks();
	/* 11 */ check(!ft_isascii(INT_MAX)); showLeaks();
	/* 12 */ check(!ft_isascii(INT_MIN)); showLeaks();

	/* Specific representative ASCII codes */
	/* 13 */ check(ft_isascii('\0')); showLeaks();
	/* 14 */ check(ft_isascii('\t')); showLeaks();
	/* 15 */ check(ft_isascii('A') && ft_isascii('a') && ft_isascii('5')); showLeaks();
	/* 16 */ check(ft_isascii(' ') && ft_isascii('~')); showLeaks();

	write(1, "\n", 1);
	return (0);
}
