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
	title("ft_strchr\t: ")

	char s[] = "tripouille";

	/* Find first */
	/* 1 first char */ check(ft_strchr(s, 't') == s); showLeaks();
	/* 2 mid char */ check(ft_strchr(s, 'l') == s + 7); showLeaks();
	/* 3 not found */ check(ft_strchr(s, 'z') == 0); showLeaks();
	/* 4 null terminator */ check(ft_strchr(s, 0) == s + strlen(s)); showLeaks();
	/* 5 char + 256 cast */ check(ft_strchr(s, 't' + 256) == s); showLeaks();

	/* First occurrence (not last) - "tripouille" first 'i' at index 2 */
	/* 6 first 'i' */ check(ft_strchr(s, 'i') == s + 2); showLeaks();

	/* Empty string */
	/* 7 empty find char */ check(ft_strchr("", 'a') == NULL); showLeaks();
	/* 8 empty find null */ char es[] = ""; check(ft_strchr(es, 0) == es); showLeaks();

	/* Single char */
	char single[] = "a";
	/* 9 single match */ check(ft_strchr(single, 'a') == single); showLeaks();
	/* 10 single nomatch */ check(ft_strchr(single, 'b') == NULL); showLeaks();

	/* Last char */
	/* 11 last char */ check(ft_strchr(s, 'e') == s + 9); showLeaks();

	/* Heap string */
	char *h = strdup("hello world");
	/* 12 heap */ check(ft_strchr(h, 'w') == h + 6); free(h); showLeaks();

	/* Compare with libc */
	const char *t = "abcdefg abc";
	/* 13 matches libc */ check(ft_strchr(t, 'b') == strchr(t, 'b')); showLeaks();
	/* 14 matches libc not found */ check(ft_strchr(t, 'z') == strchr(t, 'z')); showLeaks();
	/* 15 matches libc null */ check(ft_strchr(t, 0) == strchr(t, 0)); showLeaks();

	/* High byte */
	char hb[] = {(char)0x80, 'A', 0};
	/* 16 high byte */ check(ft_strchr(hb, 0x80) == hb); showLeaks();
	/* 17 negative cast */ check(ft_strchr(hb, -128) == hb); showLeaks();

	write(1, "\n", 1);
	return (0);
}
