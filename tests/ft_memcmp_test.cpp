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

int iTest = 1;

static int sgn(int x) { return (x > 0) - (x < 0); }

int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_memcmp\t: ")

	char s[] = {-128, 0, 127, 0};
	char sCpy[] = {-128, 0, 127, 0};
	char s2[] = {0, 0, 127, 0};
	char s3[] = {0, 0, 42, 0};

	/* 1 equal */ check(!ft_memcmp(s, sCpy, 4)); showLeaks();
	/* 2 zero length always equal */ check(!ft_memcmp(s, s2, 0)); showLeaks();
	/* 3 negative byte > 0 */ check(ft_memcmp(s, s2, 1) > 0); showLeaks();
	/* 4 reverse */ check(ft_memcmp(s2, s, 1) < 0); showLeaks();
	/* 5 different */ check(ft_memcmp(s2, s3, 4) != 0); showLeaks();

	/* Equal strings */
	/* 6 equal "abc" */ check(ft_memcmp("abc", "abc", 3) == 0); showLeaks();
	/* 7 equal length 0 even with diff */ check(ft_memcmp("abc", "xyz", 0) == 0); showLeaks();

	/* Unsigned comparison: 0xFF > 0x01 */
	unsigned char a[] = {0x01};
	unsigned char b[] = {0xFF};
	/* 8 unsigned compare */ check(ft_memcmp(a, b, 1) < 0); showLeaks();
	/* 9 reverse unsigned */ check(ft_memcmp(b, a, 1) > 0); showLeaks();

	/* Match libc sign */
	/* 10 sign matches libc */ check(sgn(ft_memcmp("Hello", "World", 5)) == sgn(memcmp("Hello", "World", 5))); showLeaks();
	/* 11 sign matches libc */ check(sgn(ft_memcmp("ABCabc", "ABCABC", 6)) == sgn(memcmp("ABCabc", "ABCABC", 6))); showLeaks();
	/* 12 sign matches libc */ check(sgn(ft_memcmp("\xFF", "\x01", 1)) == sgn(memcmp("\xFF", "\x01", 1))); showLeaks();

	/* Stops at first diff */
	/* 13 stops at first diff */ check(ft_memcmp("abcd", "abce", 3) == 0); showLeaks();
	/* 14 differ at last */ check(ft_memcmp("abcd", "abce", 4) != 0); showLeaks();

	/* Includes \0 byte */
	/* 15 reads past nulls */ check(ft_memcmp("ab\0cd", "ab\0xy", 5) != 0); showLeaks();
	/* 16 reads past nulls equal */ check(ft_memcmp("ab\0cd", "ab\0cd", 5) == 0); showLeaks();

	/* Long buffer */
	char x[100], y[100];
	memset(x, 'a', 100); memset(y, 'a', 100);
	/* 17 long equal */ check(ft_memcmp(x, y, 100) == 0); showLeaks();
	y[99] = 'b';
	/* 18 long diff at end */ check(ft_memcmp(x, y, 100) != 0); showLeaks();
	/* 19 long match within range */ check(ft_memcmp(x, y, 99) == 0); showLeaks();

	write(1, "\n", 1);
	return (0);
}
