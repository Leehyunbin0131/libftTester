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
	title("ft_memchr\t: ")

	char s[] = {0, 1, 2 ,3 ,4 ,5};

	/* Basic boundary tests */
	/* 1 zero length returns NULL */ check(ft_memchr(s, 0, 0) == NULL); showLeaks();
	/* 2 first byte */ check(ft_memchr(s, 0, 1) == s); showLeaks();
	/* 3 mid */ check(ft_memchr(s, 2, 3) == s + 2); showLeaks();
	/* 4 not found */ check(ft_memchr(s, 6, 6) == NULL); showLeaks();
	/* 5 cast to unsigned char */ check(ft_memchr(s, 2 + 256, 3) == s + 2); showLeaks();

	/* Find first occurrence (not last) */
	char dup[] = {1, 2, 3, 2, 1};
	/* 6 first occurrence */ check(ft_memchr(dup, 2, 5) == dup + 1); showLeaks();
	/* 7 not in range */ check(ft_memchr(dup, 3, 2) == NULL); showLeaks();
	/* 8 found at end */ check(ft_memchr(dup, 1, 5) == dup); showLeaks();

	/* Strings with \0 inside */
	char s2[] = {'a', 0, 'b', 'c', 0};
	/* 9 find null byte */ check(ft_memchr(s2, 0, 5) == s2 + 1); showLeaks();
	/* 10 char after null */ check(ft_memchr(s2, 'b', 5) == s2 + 2); showLeaks();
	/* 11 length excludes the byte */ check(ft_memchr(s2, 'c', 3) == NULL); showLeaks();

	/* Negative char (cast as unsigned char) */
	unsigned char u[] = {0x10, 0xFF, 0x80, 0x42};
	/* 12 high byte 0xFF */ check(ft_memchr(u, 0xFF, 4) == u + 1); showLeaks();
	/* 13 high byte 0x80 */ check(ft_memchr(u, 0x80, 4) == u + 2); showLeaks();
	/* 14 negative -1 == 0xFF */ check(ft_memchr(u, -1, 4) == u + 1); showLeaks();

	/* Compare with libc */
	char buf[] = "tripouille is awesome";
	/* 15 matches libc */ check(ft_memchr(buf, 'a', 21) == memchr(buf, 'a', 21)); showLeaks();
	/* 16 matches libc when not found */ check(ft_memchr(buf, 'z', 21) == memchr(buf, 'z', 21)); showLeaks();

	/* Last byte */
	/* 17 last byte */ check(ft_memchr(s, 5, 6) == s + 5); showLeaks();
	/* 18 length 1 found */ check(ft_memchr(s, 0, 1) == s); showLeaks();
	/* 19 length 1 not found */ check(ft_memchr(s, 5, 1) == NULL); showLeaks();

	write(1, "\n", 1);
	return (0);
}
