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
	title("ft_toupper\t: ")

	/* Boundary cases */
	/* 1 */ check(ft_toupper('a' - 1) == 'a' - 1); showLeaks();
	/* 2 */ check(ft_toupper('a') == 'A'); showLeaks();
	/* 3 */ check(ft_toupper('z' + 1) == 'z' + 1); showLeaks();
	/* 4 */ check(ft_toupper('z') == 'Z'); showLeaks();

	/* All lowercase letters convert to uppercase */
	int ok = 1;
	for (char c = 'a'; c <= 'z'; ++c)
		if (ft_toupper(c) != c - 32)
			ok = 0;
	/* 5 all 'a'..'z' converted */ check(ok); showLeaks();

	/* Uppercase letters stay the same */
	ok = 1;
	for (char c = 'A'; c <= 'Z'; ++c)
		if (ft_toupper(c) != c)
			ok = 0;
	/* 6 all 'A'..'Z' unchanged */ check(ok); showLeaks();

	/* Compare full ASCII range with libc */
	ok = 1;
	for (int c = 0; c < 128; ++c)
		if (ft_toupper(c) != toupper(c))
			ok = 0;
	/* 7 entire ASCII matches libc */ check(ok); showLeaks();

	/* Non-letter characters unchanged */
	/* 8 */ check(ft_toupper('0') == '0'); showLeaks();
	/* 9 */ check(ft_toupper('9') == '9'); showLeaks();
	/* 10 */ check(ft_toupper(' ') == ' '); showLeaks();
	/* 11 */ check(ft_toupper('!') == '!'); showLeaks();
	/* 12 */ check(ft_toupper('@') == '@'); showLeaks();
	/* 13 */ check(ft_toupper('[') == '['); showLeaks();
	/* 14 */ check(ft_toupper('`') == '`'); showLeaks();
	/* 15 */ check(ft_toupper('{') == '{'); showLeaks();

	/* Special / out-of-range values pass through unchanged */
	/* 16 */ check(ft_toupper(0) == 0); showLeaks();
	/* 17 */ check(ft_toupper(127) == 127); showLeaks();
	/* 18 */ check(ft_toupper(-1) == -1); showLeaks();
	/* 19 */ check(ft_toupper(128) == 128); showLeaks();
	/* 20 */ check(ft_toupper(255) == 255); showLeaks();

	write(1, "\n", 1);
	return (0);
}
