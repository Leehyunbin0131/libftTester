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
	title("ft_strnstr\t: ")

	char haystack[30] = "aaabcabcd";
	char needle[10] = "aabc";
	char *empty = (char *)"";

	/* 1 zero len */ check(ft_strnstr(haystack, needle, 0) == 0); showLeaks();
	/* 2 first occurrence */ check(ft_strnstr(haystack, needle, -1) == haystack + 1); showLeaks();
	/* 3 single char */ check(ft_strnstr(haystack, "a", -1) == haystack); showLeaks();
	/* 4 mid char */ check(ft_strnstr(haystack, "c", -1) == haystack + 4); showLeaks();
	/* 5 empty needle empty haystack */ check(ft_strnstr(empty, "", -1) == empty); showLeaks();
	/* 6 zero len empty needle */ check(ft_strnstr(empty, "", 0) == empty); showLeaks();
	/* 7 empty haystack non-empty needle */ check(ft_strnstr(empty, "coucou", -1) == 0); showLeaks();
	/* 8 exact length match */ check(ft_strnstr(haystack, "aaabc", 5) == haystack); showLeaks();
	/* 9 empty haystack */ check(ft_strnstr(empty, "12345", 5) == 0); showLeaks();
	/* 10 partial finds at idx 5 */ check(ft_strnstr(haystack, "abcd", 9) == haystack + 5); showLeaks();
	/* 11 length too small */ check(ft_strnstr(haystack, "cd", 8) == NULL); showLeaks();
	/* 12 mbueno-g */ check(ft_strnstr(haystack, "a", 1) == haystack); showLeaks();
	/* 13 opsec */ check(ft_strnstr("1", "a", 1) == NULL); showLeaks();
	/* 14 opsec */ check(ft_strnstr("22", "b", 2) == NULL); showLeaks();

	/* Empty needle returns haystack */
	char any[] = "anystring";
	/* 15 empty needle big haystack */ check(ft_strnstr(any, "", 5) == any); showLeaks();
	/* 16 empty needle len=0 */ check(ft_strnstr(any, "", 0) == any); showLeaks();

	/* Needle equals haystack */
	char trip[] = "Tripouille";
	/* 17 needle == haystack */ check(ft_strnstr(trip, "Tripouille", 10) == trip); showLeaks();

	/* Needle longer than haystack */
	/* 18 needle longer */ check(ft_strnstr("abc", "abcd", 100) == NULL); showLeaks();

	/* Length cuts off needle */
	/* 19 cuts at last char */ check(ft_strnstr("abcdef", "def", 5) == NULL); showLeaks();
	/* 20 just enough */ check(ft_strnstr("abcdef", "def", 6) == (char *)"abcdef" + 3); showLeaks();

	/* Match at end */
	char abcxyz[] = "abcXYZ";
	/* 21 match at very end */ check(ft_strnstr(abcxyz, "XYZ", 6) == abcxyz + 3); showLeaks();

	/* Repeated patterns */
	char rep[] = "xxabxxabxx";
	/* 22 repeated find first */ check(ft_strnstr(rep, "ab", 100) == rep + 2); showLeaks();

	/* Compare with libc strnstr (BSD-only, fallback comparison) */
	char ab[] = "ababcd";
	/* 23 cuts mid needle */ check(ft_strnstr(ab, "abcd", 5) == NULL); showLeaks();
	/* 24 just-fits second match */ check(ft_strnstr(ab, "abcd", 6) == ab + 2); showLeaks();

	/* Length 0 with empty needle returns haystack */
	char te[] = "test";
	/* 25 strange edge */ check(ft_strnstr(te, "", 0) == te); showLeaks();

	write(1, "\n", 1);
	return (0);
}
