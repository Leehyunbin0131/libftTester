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
	title("ft_strlcpy\t: ")

	char src[] = "coucou";
	char dest[10]; memset(dest, 'A', 10);

	/* 1 dstsize 0 */ check(ft_strlcpy(dest, src, 0) == strlen(src) && dest[0] == 'A'); showLeaks();
	/* 2 dstsize 1 */ check(ft_strlcpy(dest, src, 1) == strlen(src) && dest[0] == 0 && dest[1] == 'A'); showLeaks();
	/* 3 dstsize 2 */ check(ft_strlcpy(dest, src, 2) == strlen(src) && dest[0] == 'c' && dest[1] == 0 && dest[2] == 'A'); showLeaks();
	/* 4 dstsize huge */ check(ft_strlcpy(dest, src, -1) == strlen(src) && !strcmp(src, dest) && dest[strlen(src) + 1] == 'A'); showLeaks(); memset(dest, 'A', 10);
	/* 5 dstsize 6 */ check(ft_strlcpy(dest, src, 6) == strlen(src) && !memcmp(src, dest, 5) && dest[5] == 0); showLeaks(); memset(dest, 'A', 10);
	/* 6 dstsize 7 */ check(ft_strlcpy(dest, src, 7) == strlen(src) && !memcmp(src, dest, 7)); showLeaks(); memset(dest, 'A', 10);
	/* 7 dstsize 8 */ check(ft_strlcpy(dest, src, 8) == strlen(src) && !memcmp(src, dest, 7)); showLeaks(); memset(dest, 'A', 10);
	/* 8 empty src */ check(ft_strlcpy(dest, "", 42) == 0 && !memcmp("", dest, 1)); showLeaks(); memset(dest, 0, 10);
	/* 9 src 1 byte dst 0 */ check(ft_strlcpy(dest, "1", 0) == 1 && dest[0] == 0); showLeaks(); memset(dest, 'A', 10);

	/* Heap buffer */
	memset(dest, 'A', 10);
	char *h = strdup("Tripouille");
	/* 10 src len 10 dstsize 5 */ check(ft_strlcpy(dest, h, 5) == 10 && !memcmp(dest, "Trip", 5)); free(h); showLeaks();

	/* Returns source length always */
	memset(dest, 'X', 10);
	/* 11 returns src len when dst small */ check(ft_strlcpy(dest, "Hello42", 3) == 7); showLeaks();

	/* Doesn't write past dstsize */
	memset(dest, 'X', 10);
	ft_strlcpy(dest, "abcdef", 4);
	/* 12 no overrun */ check(dest[3] == 0 && dest[4] == 'X'); showLeaks();

	/* Single char source */
	memset(dest, 'A', 10);
	/* 13 single src */ check(ft_strlcpy(dest, "a", 10) == 1 && dest[0] == 'a' && dest[1] == 0); showLeaks();

	/* Compare with libc strlcpy where available - use bsd-equivalent: snprintf style */
	memset(dest, 0, 10);
	size_t r = ft_strlcpy(dest, "ABC", 10);
	/* 14 NUL-terminates */ check(r == 3 && dest[3] == 0); showLeaks();

	/* Exact-fit */
	memset(dest, 'A', 10);
	/* 15 exact fit dstsize=len+1 */ check(ft_strlcpy(dest, "12345", 6) == 5 && !strcmp(dest, "12345")); showLeaks();

	write(1, "\n", 1);
	return (0);
}
