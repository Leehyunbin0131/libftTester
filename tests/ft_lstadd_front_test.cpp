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
	title("ft_lstadd_front\t: ")

	/* Add to empty list */
	t_list *l = NULL;
	ft_lstadd_front(&l, ft_lstnew((void *)1));
	/* 1 content */ check(l && l->content == (void *)1);
	/* 2 next NULL */ check(l && l->next == 0);

	/* Add second */
	ft_lstadd_front(&l, ft_lstnew((void *)2));
	/* 3 new head content */ check(l->content == (void *)2);
	/* 4 second is old head */ check(((t_list *)l->next)->content == (void *)1);
	/* 5 second's next is NULL */ check(((t_list *)l->next)->next == 0);

	/* Add many - verify order is reversed */
	ft_lstadd_front(&l, ft_lstnew((void *)3));
	ft_lstadd_front(&l, ft_lstnew((void *)4));
	t_list *cur = l;
	int expected[] = {4, 3, 2, 1};
	int ok = 1;
	for (int i = 0; i < 4; ++i) {
		if (!cur || cur->content != (void *)(long)expected[i]) ok = 0;
		cur = cur ? (t_list *)cur->next : NULL;
	}
	/* 6 four nodes order */ check(ok && cur == NULL);
	freeList(l); showLeaks();

	/* Adding to a list of size N produces size N+1 with new head */
	t_list *base = NULL;
	for (long i = 0; i < 5; ++i)
		ft_lstadd_back(&base, ft_lstnew((void *)i));
	ft_lstadd_front(&base, ft_lstnew((void *)999));
	/* 7 new head */ check(base->content == (void *)999);
	/* 8 second is old head */ check(((t_list *)base->next)->content == (void *)0);
	/* 9 size grew to 6 */ check(ft_lstsize(base) == 6);
	freeList(base); showLeaks();

	write(1, "\n", 1);
	return (0);
}
