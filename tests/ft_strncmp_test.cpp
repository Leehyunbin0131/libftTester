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

int iTest = 1;

static int sgn(int x) { return (x > 0) - (x < 0); }

int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_strncmp\t: ")

	/* Zero length */
	/* 1 zero length always 0 */ check(ft_strncmp("t", "", 0) == 0); showLeaks();

	/* Equal prefix */
	/* 2 equal prefix */ check(ft_strncmp("1234", "1235", 3) == 0); showLeaks();
	/* 3 differ at last */ check(ft_strncmp("1234", "1235", 4) < 0); showLeaks();
	/* 4 huge length */ check(ft_strncmp("1234", "1235", -1) < 0); showLeaks();

	/* Both empty */
	/* 5 both empty */ check(ft_strncmp("", "", 42) == 0); showLeaks();
	/* 6 same string */ check(ft_strncmp("Tripouille", "Tripouille", 42) == 0); showLeaks();

	/* Case sensitivity */
	/* 7 case diff */ check(ft_strncmp("Tripouille", "tripouille", 42) < 0); showLeaks();
	/* 8 case mid diff */ check(ft_strncmp("Tripouille", "TriPouille", 42) > 0); showLeaks();
	/* 9 case end diff */ check(ft_strncmp("Tripouille", "TripouillE", 42) > 0); showLeaks();

	/* Length differences */
	/* 10 longer */ check(ft_strncmp("Tripouille", "TripouilleX", 42) < 0); showLeaks();
	/* 11 shorter */ check(ft_strncmp("Tripouille", "Tripouill", 42) > 0); showLeaks();

	/* Zero len with diff strings */
	/* 12 */ check(ft_strncmp("", "1", 0) == 0); showLeaks();
	/* 13 */ check(ft_strncmp("1", "", 0) == 0); showLeaks();
	/* 14 */ check(ft_strncmp("", "1", 1) < 0); showLeaks();
	/* 15 */ check(ft_strncmp("1", "", 1) > 0); showLeaks();
	/* 16 */ check(ft_strncmp("", "", 1) == 0); showLeaks();

	/* Negative char (signed char min) - matches libc behavior */
	signed char str1[] = "test";
	signed char str2[] = "test";
	size_t len = strlen((const char *)str1);
	str2[3] = SCHAR_MIN;
	/* 17 SCHAR_MIN cmp */ check(sgn(ft_strncmp((const char *)str1, (const char *)str2, len)) == sgn(strncmp((const char *)str1, (const char *)str2, len))); showLeaks();
	str2[3] = -42;
	/* 18 -42 cmp */ check(sgn(ft_strncmp((const char *)str1, (const char *)str2, len)) == sgn(strncmp((const char *)str1, (const char *)str2, len))); showLeaks();

	/* Comparison stops on null in either */
	/* 19 stops at null */ check(ft_strncmp("ab\0XX", "ab\0YY", 5) == 0); showLeaks();
	/* 20 stops at null vs non-null */ check(ft_strncmp("ab\0", "abc", 4) < 0); showLeaks();

	/* Length restricts comparison */
	/* 21 restricted by n */ check(ft_strncmp("abc", "abd", 2) == 0); showLeaks();
	/* 22 with n=0 anything equal */ check(ft_strncmp("ABC", "xyz", 0) == 0); showLeaks();

	/* Sign matches libc on entire range */
	const char *pairs[][2] = {
		{"a", "b"}, {"b", "a"}, {"abc", "abd"}, {"abd", "abc"},
		{"AB", "ab"}, {"hello", "hellp"}, {"42", "42 "},
	};
	int ok = 1;
	for (size_t i = 0; i < sizeof(pairs)/sizeof(pairs[0]); ++i)
		if (sgn(ft_strncmp(pairs[i][0], pairs[i][1], 100)) != sgn(strncmp(pairs[i][0], pairs[i][1], 100)))
			ok = 0;
	/* 23 sign matches libc table */ check(ok); showLeaks();

	write(1, "\n", 1);
	return (0);
}
