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
	title("ft_tolower\t: ")

	/* Boundary cases */
	/* 1 */ check(ft_tolower('A' - 1) == 'A' - 1); showLeaks();
	/* 2 */ check(ft_tolower('A') == 'a'); showLeaks();
	/* 3 */ check(ft_tolower('Z' + 1) == 'Z' + 1); showLeaks();
	/* 4 */ check(ft_tolower('Z') == 'z'); showLeaks();

	/* All uppercase letters convert to lowercase */
	int ok = 1;
	for (char c = 'A'; c <= 'Z'; ++c)
		if (ft_tolower(c) != c + 32)
			ok = 0;
	/* 5 all 'A'..'Z' converted */ check(ok); showLeaks();

	/* Lowercase letters stay the same */
	ok = 1;
	for (char c = 'a'; c <= 'z'; ++c)
		if (ft_tolower(c) != c)
			ok = 0;
	/* 6 all 'a'..'z' unchanged */ check(ok); showLeaks();

	/* Compare full ASCII range with libc */
	ok = 1;
	for (int c = 0; c < 128; ++c)
		if (ft_tolower(c) != tolower(c))
			ok = 0;
	/* 7 entire ASCII matches libc */ check(ok); showLeaks();

	/* Non-letter characters unchanged */
	/* 8 */ check(ft_tolower('0') == '0'); showLeaks();
	/* 9 */ check(ft_tolower('5') == '5'); showLeaks();
	/* 10 */ check(ft_tolower(' ') == ' '); showLeaks();
	/* 11 */ check(ft_tolower('!') == '!'); showLeaks();
	/* 12 */ check(ft_tolower('@') == '@'); showLeaks();
	/* 13 */ check(ft_tolower('[') == '['); showLeaks();
	/* 14 */ check(ft_tolower('`') == '`'); showLeaks();
	/* 15 */ check(ft_tolower('{') == '{'); showLeaks();

	/* Special / out-of-range values pass through unchanged */
	/* 16 */ check(ft_tolower(0) == 0); showLeaks();
	/* 17 */ check(ft_tolower(127) == 127); showLeaks();
	/* 18 */ check(ft_tolower(-1) == -1); showLeaks();
	/* 19 */ check(ft_tolower(128) == 128); showLeaks();
	/* 20 */ check(ft_tolower(255) == 255); showLeaks();

	write(1, "\n", 1);
	return (0);
}
