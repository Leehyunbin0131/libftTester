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

static void iter(unsigned int i, char *s) { *s = (char)(*s + i); }
static void toUpper(unsigned int i, char *s) { (void)i; if (*s >= 'a' && *s <= 'z') *s -= 32; }
static void toggleParity(unsigned int i, char *s) { if (i % 2) *s = (char)(*s + 1); }

int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_striteri\t: ")

	/* Empty string */
	{
		char s[] = "";
		ft_striteri(s, iter);
		/* 1 empty */ check(!strcmp(s, ""));
	}
	showLeaks();

	/* Single char */
	{
		char s[] = "0";
		ft_striteri(s, iter);
		/* 2 single */ check(!strcmp(s, "0"));
	}
	showLeaks();

	/* Index addition pattern */
	{
		char s[] = "0000000000";
		ft_striteri(s, iter);
		/* 3 index added */ check(!strcmp(s, "0123456789"));
	}
	showLeaks();

	/* Modifies in place */
	{
		char s[] = "hello";
		ft_striteri(s, toUpper);
		/* 4 in-place upper */ check(!strcmp(s, "HELLO"));
	}
	showLeaks();

	/* Index parity */
	{
		char s[] = "AAAA";
		ft_striteri(s, toggleParity);
		/* 5 even idx unchanged, odd idx +1 */ check(!strcmp(s, "ABAB"));
	}
	showLeaks();

	/* Long string */
	{
		char s[101]; memset(s, 'A', 100); s[100] = 0;
		ft_striteri(s, toUpper);
		int ok = 1;
		for (int i = 0; i < 100; ++i) if (s[i] != 'A') ok = 0;
		/* 6 long unchanged */ check(ok && s[100] == 0);
	}
	showLeaks();

	/* Char modification reflects in original buffer */
	{
		char *h = strdup("abcd");
		ft_striteri(h, toUpper);
		/* 7 heap modified */ check(!strcmp(h, "ABCD"));
		free(h);
	}
	showLeaks();

	/* Indexing starts at 0 */
	{
		char s[] = "X";
		ft_striteri(s, iter);
		/* 8 first index 0 */ check(s[0] == 'X');
	}
	showLeaks();

	write(1, "\n", 1);
	return (0);
}
