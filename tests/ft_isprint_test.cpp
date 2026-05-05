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
	title("ft_isprint\t: ")

	/* Boundaries: printable is [' ' (0x20), '~' (0x7E)] */
	/* 1 */ check(!ft_isprint(' ' - 1)); showLeaks();
	/* 2 */ check(ft_isprint(' ')); showLeaks();
	/* 3 */ check(!ft_isprint('~' + 1)); showLeaks();
	/* 4 */ check(ft_isprint('~')); showLeaks();

	/* Entire ASCII matches libc */
	int ok = 1;
	for (int c = 0; c < 128; ++c)
		if (!!ft_isprint(c) != !!isprint(c))
			ok = 0;
	/* 5 entire ASCII matches libc */ check(ok); showLeaks();

	/* Control chars must NOT be printable */
	ok = 1;
	for (int c = 0; c < 32; ++c)
		if (ft_isprint(c))
			ok = 0;
	/* 6 control chars [0,31] not printable */ check(ok); showLeaks();

	/* All chars in [32, 126] must be printable */
	ok = 1;
	for (int c = 32; c < 127; ++c)
		if (!ft_isprint(c))
			ok = 0;
	/* 7 all of [' ', '~'] is printable */ check(ok); showLeaks();

	/* DEL and beyond not printable */
	/* 8 */ check(!ft_isprint(127)); showLeaks();
	/* 9 */ check(!ft_isprint(128)); showLeaks();
	/* 10 */ check(!ft_isprint(255)); showLeaks();

	/* Edge values */
	/* 11 */ check(!ft_isprint(0)); showLeaks();
	/* 12 */ check(!ft_isprint('\t')); showLeaks();
	/* 13 */ check(!ft_isprint('\n')); showLeaks();
	/* 14 */ check(!ft_isprint(-1)); showLeaks();
	/* 15 */ check(!ft_isprint(INT_MAX)); showLeaks();
	/* 16 */ check(!ft_isprint(INT_MIN)); showLeaks();

	/* Sample valid */
	/* 17 */ check(ft_isprint('A') && ft_isprint('5') && ft_isprint('!')); showLeaks();

	write(1, "\n", 1);
	return (0);
}
