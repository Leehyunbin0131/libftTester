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
	title("ft_strdup\t: ")

	/* Standard */
	char *s = ft_strdup((char *)"coucou");
	/* 1 content */ check(s && !strcmp(s, "coucou"));
	/* 2 size */ mcheck(s, strlen("coucou") + 1); free(s); showLeaks();

	/* Empty */
	s = ft_strdup((char *)"");
	/* 3 empty */ check(s && !strcmp(s, ""));
	/* 4 empty size */ mcheck(s, 1); free(s); showLeaks();

	/* Single char */
	s = ft_strdup("a");
	/* 5 single */ check(s && !strcmp(s, "a"));
	/* 6 single size */ mcheck(s, 2); free(s); showLeaks();

	/* Long string */
	char big[1001]; memset(big, 'X', 1000); big[1000] = 0;
	s = ft_strdup(big);
	/* 7 long content */ check(s && !strcmp(s, big));
	/* 8 long size */ mcheck(s, 1001); free(s); showLeaks();

	/* Special chars */
	s = ft_strdup("Hello, World!\n\t");
	/* 9 special */ check(s && !strcmp(s, "Hello, World!\n\t")); free(s); showLeaks();

	/* Returned pointer must differ from source (newly allocated) */
	const char *src = "tripouille";
	s = ft_strdup(src);
	/* 10 different ptr */ check(s != src); free(s); showLeaks();

	/* Modifying the duplicate must not affect the source */
	const char *orig = "abcd";
	char *cp = ft_strdup(orig);
	cp[0] = 'X';
	/* 11 independent copy */ check(orig[0] == 'a' && cp[0] == 'X'); free(cp); showLeaks();

	/* High byte content */
	char hb[] = {(char)0x80, 'A', 'B', 0};
	s = ft_strdup(hb);
	/* 12 high byte */ check(s && (unsigned char)s[0] == 0x80 && s[1] == 'A' && s[2] == 'B' && s[3] == 0);
	free(s); showLeaks();

	write(1, "\n", 1);
	return (0);
}
