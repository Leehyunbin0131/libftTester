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
	title("ft_isalpha\t: ")

	/* Boundary values around the alpha ranges */
	/* 1 */ check(!ft_isalpha('a' - 1)); showLeaks();
	/* 2 */ check(ft_isalpha('a')); showLeaks();
	/* 3 */ check(!ft_isalpha('z' + 1)); showLeaks();
	/* 4 */ check(ft_isalpha('z')); showLeaks();
	/* 5 */ check(!ft_isalpha('A' - 1)); showLeaks();
	/* 6 */ check(ft_isalpha('A')); showLeaks();
	/* 7 */ check(!ft_isalpha('Z' + 1)); showLeaks();
	/* 8 */ check(ft_isalpha('Z')); showLeaks();

	/* Each character of the entire ASCII range vs libc reference */
	int ok = 1;
	for (int c = 0; c < 128; ++c)
		if (!!ft_isalpha(c) != !!isalpha(c))
			ok = 0;
	/* 9 entire ASCII matches libc */ check(ok); showLeaks();

	/* Special values */
	/* 10 */ check(!ft_isalpha(0)); showLeaks();
	/* 11 */ check(!ft_isalpha(' ')); showLeaks();
	/* 12 */ check(!ft_isalpha('\t')); showLeaks();
	/* 13 */ check(!ft_isalpha('\n')); showLeaks();
	/* 14 */ check(!ft_isalpha('0')); showLeaks();
	/* 15 */ check(!ft_isalpha('9')); showLeaks();
	/* 16 */ check(!ft_isalpha(127)); showLeaks();
	/* 17 */ check(!ft_isalpha(128)); showLeaks();
	/* 18 */ check(!ft_isalpha(255)); showLeaks();
	/* 19 */ check(!ft_isalpha(-1)); showLeaks(); /* EOF */
	/* 20 */ check(!ft_isalpha(INT_MAX)); showLeaks();
	/* 21 */ check(!ft_isalpha(INT_MIN)); showLeaks();

	/* Random sample of letters */
	/* 22 */ check(ft_isalpha('m') && ft_isalpha('M')); showLeaks();
	/* 23 */ check(ft_isalpha('q') && ft_isalpha('Q')); showLeaks();

	write(1, "\n", 1);
	return (0);
}
