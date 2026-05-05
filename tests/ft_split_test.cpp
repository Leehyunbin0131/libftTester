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

void freeTab(char **tab)
{
	if (!tab) return;
	for (int i = 0; tab[i] != NULL; ++i)
		free(tab[i]);
	free(tab);
}

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_split\t: ")

	char **tab = ft_split("  tripouille  42  ", ' ');
	/* 1 */ mcheck(tab, sizeof(char *) * 3);
	/* 2 */ check(!strcmp(tab[0], "tripouille"));
	/* 3 */ mcheck(tab[0], strlen("tripouille") + 1);
	/* 4 */ check(!strcmp(tab[1], "42"));
	/* 5 */ mcheck(tab[1], strlen("42") + 1);
	/* 6 */ check(tab[2] == NULL);
	freeTab(tab); showLeaks();

	tab = ft_split("tripouille", 0);
	/* 7 single token sep null */ check(!strcmp(tab[0], "tripouille"));
	/* 8 */ check(tab[1] == NULL);
	freeTab(tab); showLeaks();

	tab = ft_split("     ", ' ');
	/* 9 only seps */ check(tab[0] == NULL);
	free(tab); showLeaks();

	char *invalidReadCheck = new char; *invalidReadCheck = 0;
	tab = ft_split(invalidReadCheck, 0);
	/* 10 */ check(tab[0] == NULL); delete invalidReadCheck;
	free(tab); showLeaks();

	tab = ft_split("chinimala", ' ');
	/* 11 */ mcheck(tab, sizeof(char *) * 2);
	/* 12 */ check(!strcmp(tab[0], "chinimala"));
	/* 13 */ check(tab[1] == NULL);
	freeTab(tab); showLeaks();

	tab = ft_split("", ' ');
	/* 14 empty input */ mcheck(tab, sizeof(char *) * 1);
	/* 15 */ check(tab[0] == NULL);
	freeTab(tab); showLeaks();

	/* sguerra- */
	char *splitme = strdup("Tripouille");
	tab = ft_split(splitme, ' ');
	/* 16 */ mcheck(tab, sizeof(char *) * 2);
	/* 17 */ check(!strcmp(tab[0], "Tripouille"));
	/* 18 */ check(tab[1] == NULL);
	free(splitme); freeTab(tab); showLeaks();

	splitme = strdup("Tripouille ");
	tab = ft_split(splitme, ' ');
	/* 19 */ mcheck(tab, sizeof(char *) * 2);
	/* 20 */ check(!strcmp(tab[0], "Tripouille"));
	/* 21 */ check(tab[1] == NULL);
	free(splitme); freeTab(tab); showLeaks();

	splitme = strdup(" Tripouille");
	tab = ft_split(splitme, ' ');
	/* 22 */ mcheck(tab, sizeof(char *) * 2);
	/* 23 */ check(!strcmp(tab[0], "Tripouille"));
	/* 24 */ check(tab[1] == NULL);
	free(splitme); freeTab(tab); showLeaks();

	splitme = strdup(" Tripouille ");
	tab = ft_split(splitme, ' ');
	/* 25 */ mcheck(tab, sizeof(char *) * 2);
	/* 26 */ check(!strcmp(tab[0], "Tripouille"));
	/* 27 */ mcheck(tab[0], strlen("Tripouille") + 1);
	/* 28 */ check(tab[1] == NULL);
	free(splitme); freeTab(tab); showLeaks();

	/* wleite - many separators */
	splitme = strdup("--1-2--3---4----5-----42");
	tab = ft_split(splitme, '-');
	/* 29 */ mcheck(tab, sizeof(char *) * 7);
	/* 30 */ check(!strcmp(tab[0], "1"));  /* 31 */ mcheck(tab[0], 2);
	/* 32 */ check(!strcmp(tab[1], "2"));  /* 33 */ mcheck(tab[1], 2);
	/* 34 */ check(!strcmp(tab[2], "3"));  /* 35 */ mcheck(tab[2], 2);
	/* 36 */ check(!strcmp(tab[3], "4"));  /* 37 */ mcheck(tab[3], 2);
	/* 38 */ check(!strcmp(tab[4], "5"));  /* 39 */ mcheck(tab[4], 2);
	/* 40 */ check(!strcmp(tab[5], "42")); /* 41 */ mcheck(tab[5], 3);
	/* 42 */ check(tab[6] == NULL);
	free(splitme); freeTab(tab); showLeaks();

	/* Multi-word with single separator */
	tab = ft_split("hello world from 42", ' ');
	/* 43 size */ mcheck(tab, sizeof(char *) * 5);
	/* 44 */ check(!strcmp(tab[0], "hello"));
	/* 45 */ check(!strcmp(tab[1], "world"));
	/* 46 */ check(!strcmp(tab[2], "from"));
	/* 47 */ check(!strcmp(tab[3], "42"));
	/* 48 */ check(tab[4] == NULL);
	freeTab(tab); showLeaks();

	/* Separator is non-space */
	tab = ft_split("a,b,c,d,e", ',');
	/* 49 */ mcheck(tab, sizeof(char *) * 6);
	/* 50 */ check(!strcmp(tab[0], "a") && !strcmp(tab[1], "b") && !strcmp(tab[2], "c") && !strcmp(tab[3], "d") && !strcmp(tab[4], "e") && tab[5] == NULL);
	freeTab(tab); showLeaks();

	/* String only of separator chars */
	tab = ft_split(",,,,,", ',');
	/* 51 */ check(tab[0] == NULL);
	freeTab(tab); showLeaks();

	/* Single char that is the separator */
	tab = ft_split("z", 'z');
	/* 52 */ check(tab[0] == NULL);
	freeTab(tab); showLeaks();

	/* Single char that is not the separator */
	tab = ft_split("z", 'a');
	/* 53 */ check(!strcmp(tab[0], "z") && tab[1] == NULL);
	freeTab(tab); showLeaks();

	/* Separator at start, end, and middle simultaneously */
	tab = ft_split("xxhelloxxworldxx", 'x');
	/* 54 */ mcheck(tab, sizeof(char *) * 3);
	/* 55 */ check(!strcmp(tab[0], "hello") && !strcmp(tab[1], "world") && tab[2] == NULL);
	freeTab(tab); showLeaks();

	/* Big input */
	char big[1001]; for (int i = 0; i < 1000; ++i) big[i] = (i % 5 == 0) ? ' ' : 'A'; big[1000] = 0;
	tab = ft_split(big, ' ');
	/* 56 big input not crash */ check(tab != NULL);
	freeTab(tab); showLeaks();

	write(1, "\n", 1);
	return (0);
}
