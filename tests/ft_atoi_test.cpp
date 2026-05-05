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
#include <stdlib.h>

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_atoi\t\t: ")

	char escape[] = {9, 10, 11, 12, 13, 0};
	string e(escape);

	/* Whitespace prefix accepted */
	/* 1 ws + 1 */ check(ft_atoi((e + "1").c_str()) == 1); showLeaks();
	/* 2 ws + non-num */ check(ft_atoi((e + "a1").c_str()) == 0); showLeaks();
	/* 3 ws + -- */ check(ft_atoi((e + "--1").c_str()) == 0); showLeaks();
	/* 4 ws + ++ */ check(ft_atoi((e + "++1").c_str()) == 0); showLeaks();
	/* 5 ws + + */ check(ft_atoi((e + "+1").c_str()) == 1); showLeaks();
	/* 6 ws + - */ check(ft_atoi((e + "-1").c_str()) == -1); showLeaks();
	/* 7 zero */ check(ft_atoi((e + "0").c_str()) == 0); showLeaks();
	/* 8 stops at non-digit */ check(ft_atoi((e + "+42lyon").c_str()) == 42); showLeaks();
	/* 9 multi-digit */ check(ft_atoi((e + "+101").c_str()) == 101); showLeaks();
	/* 10 INT_MAX */ check(ft_atoi((e + to_string(INT_MAX)).c_str()) == INT_MAX); showLeaks();
	/* 11 INT_MIN */ check(ft_atoi((e + to_string(INT_MIN)).c_str()) == INT_MIN); showLeaks();
	/* 12 -+ */ check(ft_atoi("-+42") == 0); showLeaks();
	/* 13 +- */ check(ft_atoi("+-42") == 0); showLeaks();
	/* 14 + ws 42 (ws after sign) */ check(ft_atoi((string("+") + e + "42").c_str()) == 0); showLeaks();
	/* 15 - ws 42 */ check(ft_atoi((string("-") + e + "42").c_str()) == 0); showLeaks();
	/* 16 1 ws 42 stops */ check(ft_atoi((string("1") + e + "42").c_str()) == 1); showLeaks();
	/* 17 -1 ws 42 stops */ check(ft_atoi((string("-1") + e + "42").c_str()) == -1); showLeaks();

	/* Empty / pure whitespace */
	/* 18 empty */ check(ft_atoi("") == 0); showLeaks();
	/* 19 only ws */ check(ft_atoi("   \t\n") == 0); showLeaks();
	/* 20 only sign */ check(ft_atoi("+") == 0); showLeaks();
	/* 21 only sign minus */ check(ft_atoi("-") == 0); showLeaks();

	/* Match libc atoi */
	const char *samples[] = {
		"42", "-42", "0", "00042", "  -123abc", "+0", "-0",
		"2147483647", "-2147483648", "10000000000", /* overflow */
		"   +321", "\t\n\v\f\r 99",
	};
	int ok = 1;
	for (size_t i = 0; i < sizeof(samples)/sizeof(samples[0]); ++i)
		if (ft_atoi(samples[i]) != atoi(samples[i]))
			ok = 0;
	/* 22 matches libc */ check(ok); showLeaks();

	/* Leading zeros */
	/* 23 leading zeros */ check(ft_atoi("000042") == 42); showLeaks();
	/* 24 -0 */ check(ft_atoi("-0") == 0); showLeaks();
	/* 25 +0 */ check(ft_atoi("+0") == 0); showLeaks();

	/* Boundary like values */
	/* 26 INT_MAX exact */ check(ft_atoi("2147483647") == 2147483647); showLeaks();
	/* 27 INT_MIN exact */ check(ft_atoi("-2147483648") == INT_MIN); showLeaks();

	/* Stops at first non-digit */
	/* 28 stops at letter */ check(ft_atoi("123abc456") == 123); showLeaks();
	/* 29 stops at space */ check(ft_atoi("12 34") == 12); showLeaks();
	/* 30 stops at . */ check(ft_atoi("3.14") == 3); showLeaks();

	/* Negative results */
	/* 31 small neg */ check(ft_atoi("-7") == -7); showLeaks();
	/* 32 big neg */ check(ft_atoi("-99999") == -99999); showLeaks();

	write(1, "\n", 1);
	return (0);
}
