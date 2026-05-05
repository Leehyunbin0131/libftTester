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
	title("ft_strlen\t: ")

	/* Basic length */
	/* 1 */ check(ft_strlen((char *)"123") == 3); showLeaks();
	/* 2 empty */ check(ft_strlen((char *)"") == 0); showLeaks();

	/* Single char */
	/* 3 single */ check(ft_strlen((char *)"a") == 1); showLeaks();

	/* Long string */
	char big[1001];
	memset(big, 'a', 1000); big[1000] = 0;
	/* 4 1000 chars */ check(ft_strlen(big) == 1000); showLeaks();

	/* Whitespace and special characters */
	/* 5 spaces */ check(ft_strlen((char *)"   ") == 3); showLeaks();
	/* 6 tabs/newlines */ check(ft_strlen((char *)"\t\n\r") == 3); showLeaks();

	/* String w/ printable + non-printable */
	/* 7 mixed */ check(ft_strlen((char *)"Hello, World!") == 13); showLeaks();
	/* 8 escape mix */ check(ft_strlen((char *)"42\n") == 3); showLeaks();

	/* Heap allocated */
	char *h = strdup("Tripouille");
	/* 9 heap */ check(ft_strlen(h) == 10); free(h); showLeaks();

	/* Compare with libc strlen */
	const char *samples[] = {"", "a", "hello", "42 born to code", "the quick brown fox"};
	int ok = 1;
	for (int i = 0; i < 5; ++i)
		if (ft_strlen(samples[i]) != strlen(samples[i]))
			ok = 0;
	/* 10 matches libc */ check(ok); showLeaks();

	/* String with high-byte chars */
	char hb[] = {(char)0x80, (char)0xFF, 'A', 0};
	/* 11 high bytes */ check(ft_strlen(hb) == 3); showLeaks();

	write(1, "\n", 1);
	return (0);
}
