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
	title("ft_substr\t: ")

	/* len bigger than string size: copy until null */
	char *s = ft_substr("tripouille", 0, 42000);
	/* 1 huge len */ check(s && !strcmp(s, "tripouille"));
	/* 2 size */ mcheck(s, strlen("tripouille") + 1); free(s); showLeaks();

	/* Single char in the middle */
	s = ft_substr("tripouille", 1, 1);
	/* 3 mid char */ check(s && !strcmp(s, "r"));
	/* 4 size */ mcheck(s, 2); free(s); showLeaks();

	/* Start past end */
	s = ft_substr("tripouille", 100, 1);
	/* 5 start past end */ check(s && !strcmp(s, ""));
	/* 6 size */ mcheck(s, 1); free(s); showLeaks();

	/* Heap input, start past end */
	char *str = strdup("1");
	s = ft_substr(str, 42, 42000000);
	/* 7 past end heap */ check(s && !strcmp(s, ""));
	/* 8 size */ mcheck(s, 1); free(s); free(str); showLeaks();

	/* mbueno-g - len > available */
	str = strdup("0123456789");
	s = ft_substr(str, 9, 10);
	/* 9 len > avail */ check(s && !strcmp(s, "9"));
	/* 10 size */ mcheck(s, 2); free(s); free(str); showLeaks();

	/* fcaquard - len 0 */
	s = ft_substr("42", 0, 0);
	/* 11 len 0 */ check(s && !strcmp(s, ""));
	/* 12 size */ mcheck(s, 1); free(s); showLeaks();

	/* dfarhi - normal slicing */
	s = ft_substr("BONJOUR LES HARICOTS !", 8, 14);
	/* 13 mid slice */ check(s && !strcmp(s, "LES HARICOTS !"));
	/* 14 size */ mcheck(s, 15); free(s); showLeaks();

	s = ft_substr("test", 1, 2);
	/* 15 dfarhi */ check(s && !strcmp(s, "es"));
	/* 16 size */ mcheck(s, 3); free(s); showLeaks();

	/* Empty input string */
	s = ft_substr("", 0, 0);
	/* 17 empty start 0 len 0 */ check(s && !strcmp(s, ""));
	/* 18 size */ mcheck(s, 1); free(s); showLeaks();

	s = ft_substr("", 0, 100);
	/* 19 empty huge len */ check(s && !strcmp(s, ""));
	/* 20 size */ mcheck(s, 1); free(s); showLeaks();

	/* Start at 0, len equals strlen */
	s = ft_substr("Hello", 0, 5);
	/* 21 full copy */ check(s && !strcmp(s, "Hello"));
	/* 22 size */ mcheck(s, 6); free(s); showLeaks();

	/* Start at last char */
	s = ft_substr("Hello", 4, 1);
	/* 23 last char */ check(s && !strcmp(s, "o"));
	/* 24 size */ mcheck(s, 2); free(s); showLeaks();

	/* Start exactly at end */
	s = ft_substr("Hello", 5, 5);
	/* 25 start at end */ check(s && !strcmp(s, ""));
	/* 26 size */ mcheck(s, 1); free(s); showLeaks();

	/* Returned pointer must be independent of source */
	const char *src = "TripOuille";
	s = ft_substr(src, 0, 4);
	/* 27 independent */ check(s && s != src && !strcmp(s, "Trip"));
	free(s); showLeaks();

	write(1, "\n", 1);
	return (0);
}
