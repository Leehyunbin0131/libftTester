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
	title("ft_strrchr\t: ")

	char s[] = "tripouille";
	char s2[] = "ltripouiel";
	char s3[] = "";

	/* Single occurrence */
	/* 1 single 't' */ check(ft_strrchr(s, 't') == s); showLeaks();
	/* 2 last 'l' */ check(ft_strrchr(s, 'l') == s + 8); showLeaks();
	/* 3 last 'l' in s2 */ check(ft_strrchr(s2, 'l') == s2 + 9); showLeaks();
	/* 4 not found */ check(ft_strrchr(s, 'z') == NULL); showLeaks();
	/* 5 null term */ check(ft_strrchr(s, 0) == s + strlen(s)); showLeaks();
	/* 6 char + 256 */ check(ft_strrchr(s, 't' + 256) == s); showLeaks();

	char *empty = (char *)calloc(1, 1);
	/* 7 empty no match */ check(ft_strrchr(empty, 'V') == NULL); free(empty); showLeaks();
	/* 8 empty find null */ check(ft_strrchr(s3, 0) == s3); showLeaks();

	/* Last occurrence (not first) - "tripouille" last 'i' at index 6 */
	/* 9 last 'i' */ check(ft_strrchr(s, 'i') == s + 6); showLeaks();
	/* 10 'r' single occ */ check(ft_strrchr(s, 'r') == s + 1); showLeaks();

	/* Multiple repeated */
	char rep[] = "aaaaa";
	/* 11 last 'a' */ check(ft_strrchr(rep, 'a') == rep + 4); showLeaks();
	char single[] = "a";
	/* 12 single char string find char */ check(ft_strrchr(single, 'a') == single); showLeaks();

	/* Single char string */
	/* 13 single char no match */ check(ft_strrchr(single, 'b') == NULL); showLeaks();

	/* Compare with libc */
	const char *t = "abc def abc";
	/* 14 matches libc found */ check(ft_strrchr(t, 'a') == strrchr(t, 'a')); showLeaks();
	/* 15 matches libc null */ check(ft_strrchr(t, 0) == strrchr(t, 0)); showLeaks();
	/* 16 matches libc not found */ check(ft_strrchr(t, 'z') == strrchr(t, 'z')); showLeaks();

	/* High byte / negative */
	char hb[] = {(char)0x80, 'A', (char)0x80, 0};
	/* 17 last high byte */ check(ft_strrchr(hb, 0x80) == hb + 2); showLeaks();
	/* 18 negative cast */ check(ft_strrchr(hb, -128) == hb + 2); showLeaks();

	write(1, "\n", 1);
	return (0);
}
