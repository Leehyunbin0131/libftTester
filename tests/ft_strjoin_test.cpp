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
	title("ft_strjoin\t: ")

	/* Basic concatenation */
	char *s = ft_strjoin("tripouille", "42");
	/* 1 content */ check(s && !strcmp(s, "tripouille42"));
	/* 2 size */ mcheck(s, strlen("tripouille") + strlen("42") + 1); free(s); showLeaks();

	/* Empty s1 */
	s = ft_strjoin("", "42");
	/* 3 empty s1 */ check(s && !strcmp(s, "42"));
	/* 4 size */ mcheck(s, strlen("42") + 1); free(s); showLeaks();

	/* Empty s2 */
	s = ft_strjoin("42", "");
	/* 5 empty s2 */ check(s && !strcmp(s, "42"));
	/* 6 size */ mcheck(s, strlen("42") + 1); free(s); showLeaks();

	/* Both empty */
	s = ft_strjoin("", "");
	/* 7 both empty */ check(s && !strcmp(s, ""));
	/* 8 size */ mcheck(s, 1); free(s); showLeaks();

	/* Long strings */
	char a[101]; memset(a, 'A', 100); a[100] = 0;
	char b[101]; memset(b, 'B', 100); b[100] = 0;
	s = ft_strjoin(a, b);
	/* 9 long content */ check(s && strlen(s) == 200 && s[0] == 'A' && s[99] == 'A' && s[100] == 'B' && s[199] == 'B');
	/* 10 long size */ mcheck(s, 201); free(s); showLeaks();

	/* Special characters */
	s = ft_strjoin("hello\n", "world\t");
	/* 11 special chars */ check(s && !strcmp(s, "hello\nworld\t")); free(s); showLeaks();

	/* Single char concat */
	s = ft_strjoin("a", "b");
	/* 12 single chars */ check(s && !strcmp(s, "ab"));
	/* 13 size */ mcheck(s, 3); free(s); showLeaks();

	/* Heap inputs */
	char *h1 = strdup("Tri");
	char *h2 = strdup("pouille");
	s = ft_strjoin(h1, h2);
	/* 14 heap inputs */ check(s && !strcmp(s, "Tripouille"));
	free(h1); free(h2); free(s); showLeaks();

	/* Result is independent allocation, not aliased */
	const char *p1 = "abc"; const char *p2 = "def";
	s = ft_strjoin(p1, p2);
	/* 15 independent ptr */ check(s != p1 && s != p2);
	free(s); showLeaks();

	write(1, "\n", 1);
	return (0);
}
