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
	title("ft_lstadd_back\t: ")

	/* Add to empty list */
	t_list *l = NULL;
	t_list *l2 = NULL;
	ft_lstadd_back(&l, ft_lstnew((void *)1));
	/* 1 head content */ check(l->content == (void *)1);
	/* 2 next NULL */ check(l->next == 0);

	/* Add second */
	ft_lstadd_back(&l, ft_lstnew((void *)2));
	/* 3 head unchanged */ check(l->content == (void *)1);
	/* 4 second content */ check(((t_list *)(l->next))->content == (void *)2);
	/* 5 second next NULL */ check(((t_list *)(l->next))->next == 0);

	/* Append a chain */
	ft_lstadd_back(&l2, ft_lstnew((void *)3));
	ft_lstadd_back(&l2, ft_lstnew((void *)4));
	ft_lstadd_back(&l, l2);
	/* 6 first */ check(l->content == (void *)1);
	/* 7 second */ check(((t_list *)(l->next))->content == (void *)2);
	/* 8 third */ check(((t_list *)(((t_list *)(l->next))->next))->content == (void *)3);
	/* 9 fourth */ check(((t_list *)((t_list *)(((t_list *)(l->next))->next))->next)->content == (void *)4);
	/* 10 last next NULL */ check(((t_list *)((t_list *)(((t_list *)(l->next))->next))->next)->next == 0);
	freeList(l); showLeaks();

	/* Adding NULL must not change list */
	t_list *l3 = ft_lstnew((void *)42);
	t_list *saved = l3;
	ft_lstadd_back(&l3, NULL);
	/* 11 NULL new unchanged */ check(l3 == saved && l3->content == (void *)42 && l3->next == NULL);
	freeList(l3); showLeaks();

	/* Add many in sequence: order preserved */
	t_list *seq = NULL;
	for (long i = 1; i <= 5; ++i)
		ft_lstadd_back(&seq, ft_lstnew((void *)i));
	t_list *cur = seq;
	int ok = 1;
	for (long i = 1; i <= 5; ++i) {
		if (!cur || cur->content != (void *)i) ok = 0;
		cur = cur ? (t_list *)cur->next : NULL;
	}
	/* 12 ordered 1..5 */ check(ok && cur == NULL);
	freeList(seq); showLeaks();

	/* Add when *lst == NULL but lst != NULL */
	t_list *empty = NULL;
	ft_lstadd_back(&empty, ft_lstnew((void *)99));
	/* 13 was NULL now has node */ check(empty && empty->content == (void *)99 && empty->next == NULL);
	freeList(empty); showLeaks();

	write(1, "\n", 1);
	return (0);
}
