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
static void *addOne(void *p) { void *r = malloc(sizeof(int)); *(int *)r = *(int *)p + 1; return r; }
static void *idDup(void *p) { void *r = malloc(sizeof(int)); *(int *)r = *(int *)p; return r; }

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_lstmap\t: ")

	/* Standard map */
	int tab[] = {0, 1, 2, 3};
	t_list *l = ft_lstnew(tab);
	for (int i = 1; i < 4; ++i)
		ft_lstadd_back(&l, ft_lstnew(tab + i));
	t_list *m = ft_lstmap(l, addOne, free);

	/* Original unchanged */
	t_list *tmp = l;
	for (int i = 0; i < 4; ++i) {
		/* 1..4 */ check(*(int *)tmp->content == i);
		tmp = (t_list *)tmp->next;
	}
	/* New list values are i+1 */
	tmp = m;
	for (int i = 0; i < 4; ++i) {
		/* 5..8 */ check(*(int *)tmp->content == i + 1);
		tmp = (t_list *)tmp->next;
	}
	/* 9 same length */ check(ft_lstsize(m) == 4);
	freeList(l); ft_lstclear(&m, free); showLeaks();

	/* Empty list - must return NULL */
	/* 10 empty input */ check(ft_lstmap(NULL, addOne, free) == NULL); showLeaks();

	/* Single element */
	int x = 42;
	t_list *one = ft_lstnew(&x);
	t_list *one_m = ft_lstmap(one, idDup, free);
	/* 11 single element */ check(one_m && *(int *)one_m->content == 42 && one_m->next == NULL);
	free(one); ft_lstclear(&one_m, free); showLeaks();

	/* New nodes are independent allocations */
	int y[] = {1};
	t_list *src = ft_lstnew(y);
	t_list *dst = ft_lstmap(src, idDup, free);
	/* 12 different content pointer */ check(dst->content != src->content);
	/* 13 different node pointer */ check(dst != src);
	free(src); ft_lstclear(&dst, free); showLeaks();

	/* Larger list and addOne function */
	int t2[] = {10, 20, 30, 40, 50};
	t_list *L = ft_lstnew(t2);
	for (int i = 1; i < 5; ++i)
		ft_lstadd_back(&L, ft_lstnew(t2 + i));
	t_list *M = ft_lstmap(L, addOne, free);
	int ok = 1;
	t_list *cur = M;
	for (int i = 0; i < 5; ++i) {
		if (!cur || *(int *)cur->content != t2[i] + 1) ok = 0;
		cur = cur ? (t_list *)cur->next : NULL;
	}
	/* 14 5-elem map */ check(ok && cur == NULL);
	freeList(L); ft_lstclear(&M, free); showLeaks();

	write(1, "\n", 1);
	return (0);
}
