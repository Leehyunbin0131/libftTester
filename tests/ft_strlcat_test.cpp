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
	title("ft_strlcat\t: ")

	char dest[30]; memset(dest, 0, 30);
	char *src = (char *)"AAAAAAAAA";
	dest[0] = 'B';
	/* 1 dstsize 0 */ check(ft_strlcat(dest, src, 0) == strlen(src) && !strcmp(dest, "B")); showLeaks();
	dest[0] = 'B';
	/* 2 dstsize 1 */ check(ft_strlcat(dest, src, 1) == 10 && !strcmp(dest, "B")); showLeaks();
	memset(dest, 'B', 4);
	/* 3 dstsize < dstlen */ check(ft_strlcat(dest, src, 3) == 3 + strlen(src) && !strcmp(dest, "BBBB")); showLeaks();
	/* 4 partial */ check(ft_strlcat(dest, src, 6) == 13 && !strcmp(dest, "BBBBA")); showLeaks();
	memset(dest, 'C', 5);
	/* 5 huge dstsize */ check(ft_strlcat(dest, src, -1) == 14 && !strcmp(dest, "CCCCCAAAAAAAAA")); showLeaks();
	memset(dest, 'C', 15);
	/* 6 dstsize after end */ check(ft_strlcat(dest, src, 17) == 24 && !strcmp(dest, "CCCCCCCCCCCCCCCA")); showLeaks();
	memset(dest, 0, 30);
	/* 7 dstsize 1 empty dst */ check(ft_strlcat(dest, src, 1) == strlen(src) && !strcmp(dest, "")); showLeaks();
	memset(dest, 0, 30); memset(dest, '1', 10);
	/* 8 dstsize less than dstlen */ check(ft_strlcat(dest, src, 5) == strlen(src) + 5 && !strcmp(dest, "1111111111")); showLeaks();
	memset(dest, 0, 30); memset(dest, '1', 10);
	/* 9 dstsize less than dstlen */ check(ft_strlcat(dest, src, 5) == strlen(src) + 5 && !strcmp(dest, "1111111111")); showLeaks();
	memset(dest, 0, 30); memset(dest, '1', 10);
	/* 10 empty src */ check(ft_strlcat(dest, "", 15) == 10 && !strcmp(dest, "1111111111")); showLeaks();
	memset(dest, 0, 30);
	/* 11 empty src empty dst */ check(ft_strlcat(dest, "", 42) == 0 && !strcmp(dest, "")); showLeaks();
	memset(dest, 0, 30);
	/* 12 empty all dstsize 0 */ check(ft_strlcat(dest, "", 0) == 0 && !strcmp(dest, "")); showLeaks();
	memset(dest, 0, 30);
	/* 13 truncate to 0 */ check(ft_strlcat(dest, "123", 1) == 3 && !strcmp(dest, "")); showLeaks();
	memset(dest, 0, 30);
	/* 14 truncate to 1 */ check(ft_strlcat(dest, "123", 2) == 3 && !strcmp(dest, "1")); showLeaks();
	memset(dest, 0, 30);
	/* 15 truncate to 2 */ check(ft_strlcat(dest, "123", 3) == 3 && !strcmp(dest, "12")); showLeaks();
	memset(dest, 0, 30);
	/* 16 exact fit */ check(ft_strlcat(dest, "123", 4) == 3 && !strcmp(dest, "123")); showLeaks();
	memset(dest, 0, 30);
	/* 17 dstsize 0 empty dst */ check(ft_strlcat(dest, "123", 0) == 3 && !strcmp(dest, "")); showLeaks();

	/* Result is always NUL-terminated when dstsize > strlen(dst) */
	memset(dest, 0, 30); strcpy(dest, "abc");
	ft_strlcat(dest, "xy", 10);
	/* 18 normal append */ check(!strcmp(dest, "abcxy")); showLeaks();

	/* Append nothing with zero-length src */
	memset(dest, 0, 30); strcpy(dest, "abc");
	/* 19 append empty */ check(ft_strlcat(dest, "", 10) == 3 && !strcmp(dest, "abc")); showLeaks();

	/* dest len exceeds dstsize - per BSD: result is dstsize + strlen(src) */
	memset(dest, 0, 30); memset(dest, 'a', 5); dest[5] = 0;
	/* 20 dst not NUL within dstsize */ check(ft_strlcat(dest, "Z", 3) == 3 + 1); showLeaks();

	write(1, "\n", 1);
	return (0);
}
