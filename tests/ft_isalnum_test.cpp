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
	title("ft_isalnum\t: ")

	/* Boundaries around all valid sub-ranges */
	/* 1 */ check(!ft_isalnum('a' - 1)); showLeaks();
	/* 2 */ check(ft_isalnum('a')); showLeaks();
	/* 3 */ check(!ft_isalnum('z' + 1)); showLeaks();
	/* 4 */ check(ft_isalnum('z')); showLeaks();
	/* 5 */ check(!ft_isalnum('A' - 1)); showLeaks();
	/* 6 */ check(ft_isalnum('A')); showLeaks();
	/* 7 */ check(!ft_isalnum('Z' + 1)); showLeaks();
	/* 8 */ check(ft_isalnum('Z')); showLeaks();
	/* 9 */ check(!ft_isalnum('0' - 1)); showLeaks();
	/* 10 */ check(ft_isalnum('0')); showLeaks();
	/* 11 */ check(!ft_isalnum('9' + 1)); showLeaks();
	/* 12 */ check(ft_isalnum('9')); showLeaks();

	/* Compare against libc for entire ASCII range */
	int ok = 1;
	for (int c = 0; c < 128; ++c)
		if (!!ft_isalnum(c) != !!isalnum(c))
			ok = 0;
	/* 13 full ASCII matches libc */ check(ok); showLeaks();

	/* 14 */ check(!ft_isalnum(0)); showLeaks();
	/* 15 */ check(!ft_isalnum(' ')); showLeaks();
	/* 16 */ check(!ft_isalnum('!')); showLeaks();
	/* 17 */ check(!ft_isalnum('@')); showLeaks();
	/* 18 */ check(!ft_isalnum('[')); showLeaks();
	/* 19 */ check(!ft_isalnum('`')); showLeaks();
	/* 20 */ check(!ft_isalnum('{')); showLeaks();
	/* 21 */ check(!ft_isalnum(127)); showLeaks();
	/* 22 */ check(!ft_isalnum(128)); showLeaks();
	/* 23 */ check(!ft_isalnum(255)); showLeaks();
	/* 24 */ check(!ft_isalnum(-1)); showLeaks();
	/* 25 */ check(!ft_isalnum(INT_MAX)); showLeaks();
	/* 26 */ check(!ft_isalnum(INT_MIN)); showLeaks();

	/* Sample valid chars */
	/* 27 */ check(ft_isalnum('5') && ft_isalnum('m') && ft_isalnum('Q')); showLeaks();

	write(1, "\n", 1);
	return (0);
}
