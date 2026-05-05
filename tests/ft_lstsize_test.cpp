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

void freeList(t_list *head) { if (head) freeList((t_list *)head->next); free(head); }

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_lstsize\t: ")

	/* NULL list */
	t_list *l = NULL;
	/* 1 NULL is 0 */ check(ft_lstsize(l) == 0);

	/* 1 element */
	ft_lstadd_front(&l, ft_lstnew((void *)1));
	/* 2 size 1 */ check(ft_lstsize(l) == 1);

	/* 2 elements */
	ft_lstadd_front(&l, ft_lstnew((void *)2));
	/* 3 size 2 */ check(ft_lstsize(l) == 2);
	freeList(l); showLeaks();

	/* Many elements */
	t_list *big = NULL;
	for (long i = 0; i < 100; ++i)
		ft_lstadd_front(&big, ft_lstnew((void *)i));
	/* 4 size 100 */ check(ft_lstsize(big) == 100);
	freeList(big); showLeaks();

	/* lstadd_back also counted */
	t_list *back = NULL;
	for (long i = 0; i < 50; ++i)
		ft_lstadd_back(&back, ft_lstnew((void *)i));
	/* 5 size 50 (back) */ check(ft_lstsize(back) == 50);
	freeList(back); showLeaks();

	/* Single node next NULL */
	t_list *one = ft_lstnew((void *)42);
	/* 6 size 1 */ check(ft_lstsize(one) == 1);
	free(one); showLeaks();

	/* Doesn't dereference next of last */
	t_list *a = ft_lstnew((void *)1);
	t_list *b = ft_lstnew((void *)2);
	a->next = b;
	/* 7 size 2 manually linked */ check(ft_lstsize(a) == 2);
	free(a); free(b); showLeaks();

	write(1, "\n", 1);
	return (0);
}
