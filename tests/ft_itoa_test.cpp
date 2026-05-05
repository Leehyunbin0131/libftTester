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
#include <climits>

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_itoa\t\t: ")

	char *s = ft_itoa(INT_MAX);
	/* 1 INT_MAX value */ check(s && !strcmp(s, to_string(INT_MAX).c_str()));
	/* 2 INT_MAX size */ mcheck(s, strlen(to_string(INT_MAX).c_str()) + 1); free(s); showLeaks();

	s = ft_itoa(INT_MIN);
	/* 3 INT_MIN value */ check(s && !strcmp(s, to_string(INT_MIN).c_str()));
	/* 4 INT_MIN size */ mcheck(s, strlen(to_string(INT_MIN).c_str()) + 1); free(s); showLeaks();

	s = ft_itoa(0);
	/* 5 zero */ check(s && !strcmp(s, "0"));
	/* 6 zero size */ mcheck(s, 2); free(s); showLeaks();

	s = ft_itoa(1);
	/* 7 one */ check(s && !strcmp(s, "1"));
	/* 8 one size */ mcheck(s, 2); free(s); showLeaks();

	s = ft_itoa(-1);
	/* 9 minus one */ check(s && !strcmp(s, "-1"));
	/* 10 minus one size */ mcheck(s, 3); free(s); showLeaks();

	s = ft_itoa(42);
	/* 11 42 */ check(s && !strcmp(s, "42"));
	/* 12 42 size */ mcheck(s, 3); free(s); showLeaks();

	/* Single digits */
	for (int i = 0; i < 10; ++i)
	{
		s = ft_itoa(i);
		char ref[2] = {(char)('0' + i), 0};
		/* 13..22 single digits */ check(s && !strcmp(s, ref)); free(s);
	}
	showLeaks();

	/* Negative single digit */
	s = ft_itoa(-9);
	/* 23 -9 */ check(s && !strcmp(s, "-9")); free(s); showLeaks();

	/* Powers of 10 */
	int powers[] = {10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
	const char *powstr[] = {"10", "100", "1000", "10000", "100000", "1000000", "10000000", "100000000", "1000000000"};
	int ok = 1;
	for (size_t i = 0; i < sizeof(powers)/sizeof(powers[0]); ++i) {
		s = ft_itoa(powers[i]);
		if (!s || strcmp(s, powstr[i])) ok = 0;
		free(s);
	}
	/* 24 powers of 10 */ check(ok); showLeaks();

	/* Negative powers */
	ok = 1;
	for (size_t i = 0; i < sizeof(powers)/sizeof(powers[0]); ++i) {
		s = ft_itoa(-powers[i]);
		string ref = "-" + string(powstr[i]);
		if (!s || strcmp(s, ref.c_str())) ok = 0;
		free(s);
	}
	/* 25 negative powers */ check(ok); showLeaks();

	/* Random values vs to_string */
	int values[] = {123, -456, 7890, -1, INT_MAX - 1, INT_MIN + 1, 999999, -999999};
	ok = 1;
	for (size_t i = 0; i < sizeof(values)/sizeof(values[0]); ++i) {
		s = ft_itoa(values[i]);
		if (!s || strcmp(s, to_string(values[i]).c_str())) ok = 0;
		free(s);
	}
	/* 26 random values */ check(ok); showLeaks();

	/* Result should be a valid string (NUL-terminated) */
	s = ft_itoa(12345);
	/* 27 NUL terminated */ check(s && s[strlen(s)] == 0); free(s); showLeaks();

	write(1, "\n", 1);
	return (0);
}
