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
	title("ft_strtrim\t: ")

	/* Trim leading */
	char *s = ft_strtrim("   xxxtripouille", " x");
	/* 1 trim leading */ check(s && !strcmp(s, "tripouille"));
	/* 2 size */ mcheck(s, strlen("tripouille") + 1); free(s); showLeaks();

	/* Trim trailing */
	s = ft_strtrim("tripouille   xxx", " x");
	/* 3 trim trailing */ check(s && !strcmp(s, "tripouille"));
	/* 4 size */ mcheck(s, strlen("tripouille") + 1); free(s); showLeaks();

	/* Trim both */
	s = ft_strtrim("   xxxtripouille   xxx", " x");
	/* 5 trim both */ check(s && !strcmp(s, "tripouille"));
	/* 6 size */ mcheck(s, strlen("tripouille") + 1); free(s); showLeaks();

	/* Whole string is trimmed */
	s = ft_strtrim("   xxx   xxx", " x");
	/* 7 all trimmed */ check(s && !strcmp(s, ""));
	/* 8 size */ mcheck(s, 1); free(s); showLeaks();

	/* Empty input */
	s = ft_strtrim("", "123");
	/* 9 empty input */ check(s && !strcmp(s, ""));
	/* 10 size */ mcheck(s, 1); free(s); showLeaks();

	/* Empty set: nothing trimmed */
	s = ft_strtrim("123", "");
	/* 11 empty set */ check(s && !strcmp(s, "123"));
	/* 12 size */ mcheck(s, 4); free(s); showLeaks();

	/* Both empty */
	s = ft_strtrim("", "");
	/* 13 both empty */ check(s && !strcmp(s, ""));
	/* 14 size */ mcheck(s, 1); free(s); showLeaks();

	/* opsec */
	s = ft_strtrim("abcdba", "acb");
	/* 15 */ check(s && !strcmp(s, "d"));
	/* 16 */ mcheck(s, 2); free(s); showLeaks();

	/* mogiyadev */
	s = ft_strtrim("ababa", "a");
	/* 17 */ check(s && !strcmp(s, "bab"));
	/* 18 */ mcheck(s, 4); free(s); showLeaks();

	/* No trimming needed */
	s = ft_strtrim("hello", "x");
	/* 19 unchanged */ check(s && !strcmp(s, "hello"));
	/* 20 size */ mcheck(s, 6); free(s); showLeaks();

	/* Single character that is in set */
	s = ft_strtrim("a", "a");
	/* 21 single char trimmed */ check(s && !strcmp(s, ""));
	/* 22 size */ mcheck(s, 1); free(s); showLeaks();

	/* Single character not in set */
	s = ft_strtrim("a", "b");
	/* 23 single char untrimmed */ check(s && !strcmp(s, "a"));
	/* 24 size */ mcheck(s, 2); free(s); showLeaks();

	/* Whitespace trim */
	s = ft_strtrim(" \t\n  Hello  \n\t ", " \t\n");
	/* 25 ws trim */ check(s && !strcmp(s, "Hello"));
	/* 26 size */ mcheck(s, 6); free(s); showLeaks();

	/* Set with multiple chars including duplicates */
	s = ft_strtrim("aabbccTripouilleabba", "ab");
	/* 27 */ check(s && !strcmp(s, "ccTripouille"));
	free(s); showLeaks();

	/* Independent allocation */
	const char *src = "  hello  ";
	s = ft_strtrim(src, " ");
	/* 28 independent */ check(s && s != src && !strcmp(s, "hello"));
	free(s); showLeaks();

	write(1, "\n", 1);
	return (0);
}
