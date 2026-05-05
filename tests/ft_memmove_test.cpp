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
int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_memmove\t: ")

	char s[] = {65, 66, 67, 68, 69, 0, 45};
	char s0[] = { 0,  0,  0,  0,  0,  0, 0};
	char sCpy[] = {65, 66, 67, 68, 69, 0, 45};
	char sResult[] = {67, 68, 67, 68, 69, 0, 45};
	char sResult2[] = {67, 67, 68, 68, 69, 0, 45};

	/* 1 non-overlap */ check(ft_memmove(s0, s, 7) == s0 && !memcmp(s, s0, 7)); showLeaks();
	/* 2 zero-length */ check(ft_memmove(s, s + 2, 0) && !memcmp(s, sCpy, 7)); showLeaks();
	/* 3 forward overlap (dst < src) */ check(ft_memmove(s, s + 2, 2) == s && !memcmp(s, sResult, 7)); showLeaks();
	/* 4 reverse overlap (dst > src) */ check(ft_memmove(sResult + 1, sResult, 2) == sResult + 1 && !memcmp(sResult, sResult2, 7)); showLeaks();

	/* Destination = source */
	char same[] = "Tripouille";
	char saved[] = "Tripouille";
	/* 5 src == dst */ check(ft_memmove(same, same, 10) == same && !memcmp(same, saved, 10)); showLeaks();

	/* NULL is allowed when n == 0 */
	/* 6 NULL ok when n=0 */ check(ft_memmove(s0, NULL, 0) == s0); showLeaks();

	/* Long forward overlap shift left */
	char buf[20]; memcpy(buf, "ABCDEFGHIJ\0\0\0\0\0\0\0\0\0\0", 20);
	ft_memmove(buf, buf + 3, 7);
	/* 7 shift left 3 */ check(!memcmp(buf, "DEFGHIJ", 7)); showLeaks();

	/* Long reverse overlap shift right */
	memcpy(buf, "ABCDEFGHIJ\0\0\0\0\0\0\0\0\0\0", 20);
	ft_memmove(buf + 3, buf, 7);
	/* 8 shift right 3 */ check(!memcmp(buf, "ABCABCDEFG", 10)); showLeaks();

	/* Match libc memmove */
	char a[30], b[30];
	memcpy(a, "abcdefghijklmno\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 30);
	memcpy(b, "abcdefghijklmno\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 30);
	ft_memmove(a + 2, a, 10);
	memmove(b + 2, b, 10);
	/* 9 matches libc */ check(!memcmp(a, b, 30)); showLeaks();

	/* Single byte */
	char one[] = "ABC";
	ft_memmove(one, one + 1, 1);
	/* 10 single byte */ check(one[0] == 'B' && one[1] == 'B' && one[2] == 'C'); showLeaks();

	write(1, "\n", 1);
	return (0);
}
