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
#include <climits>

static char addOne(unsigned int i, char c) { return (char)(i + c); }
static char identity(unsigned int i, char c) { (void)i; return c; }
static char upper(unsigned int i, char c) { (void)i; return (char)((c >= 'a' && c <= 'z') ? c - 32 : c); }
static char zero(unsigned int i, char c) { (void)i; (void)c; return 0; }
static char xorIdx(unsigned int i, char c) { return (char)(c ^ (i & 0x07)); }

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_strmapi\t: ")

	/* Basic transformation: c + i */
	char *s = ft_strmapi("1234", addOne);
	/* 1 c+i */ check(s && !strcmp(s, "1357"));
	/* 2 size */ mcheck(s, strlen("1357") + 1); free(s); showLeaks();

	/* Empty input */
	s = ft_strmapi("", addOne);
	/* 3 empty */ check(s && !strcmp(s, ""));
	/* 4 size */ mcheck(s, 1); free(s); showLeaks();

	/* Identity */
	s = ft_strmapi("Tripouille", identity);
	/* 5 identity */ check(s && !strcmp(s, "Tripouille"));
	/* 6 size */ mcheck(s, strlen("Tripouille") + 1); free(s); showLeaks();

	/* Uppercase */
	s = ft_strmapi("hello world", upper);
	/* 7 upper */ check(s && !strcmp(s, "HELLO WORLD"));
	/* 8 size */ mcheck(s, strlen("HELLO WORLD") + 1); free(s); showLeaks();

	/* All zero - result should be empty due to first \0 */
	s = ft_strmapi("abcdef", zero);
	/* 9 zero func makes empty */ check(s && s[0] == 0); free(s); showLeaks();

	/* Returned pointer must differ from source (independent) */
	const char *src = "Test";
	s = ft_strmapi(src, identity);
	/* 10 independent */ check(s && s != src && !strcmp(s, "Test"));
	free(s); showLeaks();

	/* Index correctness with xor pattern */
	s = ft_strmapi("AAAAAAAA", xorIdx);
	int ok = 1;
	for (int i = 0; i < 8; ++i)
		if ((unsigned char)s[i] != ('A' ^ (i & 0x07))) ok = 0;
	/* 11 index correctness */ check(s && ok && s[8] == 0); free(s); showLeaks();

	/* Single char */
	s = ft_strmapi("Z", identity);
	/* 12 single char */ check(s && !strcmp(s, "Z"));
	/* 13 size */ mcheck(s, 2); free(s); showLeaks();

	/* Long input */
	char big[101]; memset(big, 'a', 100); big[100] = 0;
	s = ft_strmapi(big, upper);
	int allUpper = 1;
	for (int i = 0; i < 100; ++i) if (s[i] != 'A') allUpper = 0;
	/* 14 long input */ check(s && allUpper && s[100] == 0);
	/* 15 size */ mcheck(s, 101); free(s); showLeaks();

	write(1, "\n", 1);
	return (0);
}
