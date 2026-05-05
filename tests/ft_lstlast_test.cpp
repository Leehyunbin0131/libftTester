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
	title("ft_lstlast\t: ")

	/* NULL list */
	t_list *l = NULL;
	/* 1 NULL */ check(ft_lstlast(l) == 0);

	/* Single element: last is itself */
	ft_lstadd_back(&l, ft_lstnew((void *)1));
	/* 2 single = self */ check(ft_lstlast(l)->content == (void *)1);

	/* Add another */
	ft_lstadd_back(&l, ft_lstnew((void *)2));
	/* 3 last is new */ check(ft_lstlast(l)->content == (void *)2);
	/* 4 last next NULL */ check(ft_lstlast(l)->next == 0);
	freeList(l); showLeaks();

	/* Many elements */
	t_list *big = NULL;
	for (long i = 1; i <= 20; ++i)
		ft_lstadd_back(&big, ft_lstnew((void *)i));
	/* 5 last of 20 */ check(ft_lstlast(big) != NULL && ft_lstlast(big)->content == (void *)20);
	/* 6 last next NULL */ check(ft_lstlast(big)->next == NULL);
	freeList(big); showLeaks();

	/* lstadd_front behavior - last is the first added */
	t_list *front = NULL;
	for (long i = 1; i <= 5; ++i)
		ft_lstadd_front(&front, ft_lstnew((void *)i));
	/* 7 lstlast after 5 lstadd_fronts is first added */ check(ft_lstlast(front)->content == (void *)1);
	freeList(front); showLeaks();

	/* Same pointer for single-node */
	t_list *one = ft_lstnew((void *)42);
	/* 8 same ptr */ check(ft_lstlast(one) == one);
	free(one); showLeaks();

	write(1, "\n", 1);
	return (0);
}
