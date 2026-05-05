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
	title("ft_isdigit\t: ")

	/* Boundary tests */
	/* 1 */ check(!ft_isdigit('0' - 1)); showLeaks();
	/* 2 */ check(ft_isdigit('0')); showLeaks();
	/* 3 */ check(!ft_isdigit('9' + 1)); showLeaks();
	/* 4 */ check(ft_isdigit('9')); showLeaks();

	/* All digits 0-9 must be true */
	int ok = 1;
	for (char c = '0'; c <= '9'; ++c)
		if (!ft_isdigit(c))
			ok = 0;
	/* 5 all '0'..'9' are digits */ check(ok); showLeaks();

	/* Compare against libc for entire ASCII range */
	ok = 1;
	for (int c = 0; c < 128; ++c)
		if (!!ft_isdigit(c) != !!isdigit(c))
			ok = 0;
	/* 6 entire ASCII matches libc */ check(ok); showLeaks();

	/* Letters that look like digits but aren't */
	/* 7 */ check(!ft_isdigit('a') && !ft_isdigit('A')); showLeaks();
	/* 8 */ check(!ft_isdigit('o') && !ft_isdigit('O')); showLeaks();

	/* Edge values */
	/* 9 */ check(!ft_isdigit(0)); showLeaks();
	/* 10 */ check(!ft_isdigit(-1)); showLeaks();
	/* 11 */ check(!ft_isdigit(127)); showLeaks();
	/* 12 */ check(!ft_isdigit(128)); showLeaks();
	/* 13 */ check(!ft_isdigit(255)); showLeaks();
	/* 14 */ check(!ft_isdigit(INT_MAX)); showLeaks();
	/* 15 */ check(!ft_isdigit(INT_MIN)); showLeaks();

	/* Spot-checks */
	/* 16 */ check(ft_isdigit('5')); showLeaks();
	/* 17 */ check(ft_isdigit('1')); showLeaks();

	write(1, "\n", 1);
	return (0);
}
