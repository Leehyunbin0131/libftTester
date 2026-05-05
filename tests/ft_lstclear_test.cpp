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

static int g_count;
static void countingFree(void *p) { ++g_count; free(p); }

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_lstclear\t: ")

	/* Standard - 11 nodes with malloc'd content */
	t_list *l = ft_lstnew(malloc(1));
	for (int i = 0; i < 10; ++i)
		ft_lstadd_front(&l, ft_lstnew(malloc(1)));
	g_count = 0;
	ft_lstclear(&l, countingFree);
	/* 1 head set to NULL */ check(l == 0);
	/* 2 del called for every node */ check(g_count == 11);
	showLeaks();

	/* Empty list */
	t_list *empty = NULL;
	g_count = 0;
	ft_lstclear(&empty, countingFree);
	/* 3 NULL list ok */ check(empty == NULL && g_count == 0);
	showLeaks();

	/* Single element */
	t_list *one = ft_lstnew(malloc(8));
	g_count = 0;
	ft_lstclear(&one, countingFree);
	/* 4 single cleared */ check(one == NULL && g_count == 1);
	showLeaks();

	/* Many nodes */
	t_list *many = NULL;
	for (int i = 0; i < 50; ++i)
		ft_lstadd_front(&many, ft_lstnew(malloc(4)));
	g_count = 0;
	ft_lstclear(&many, countingFree);
	/* 5 50 cleared */ check(many == NULL && g_count == 50);
	showLeaks();

	/* String content with strdup */
	t_list *strs = NULL;
	ft_lstadd_back(&strs, ft_lstnew(strdup("a")));
	ft_lstadd_back(&strs, ft_lstnew(strdup("bb")));
	ft_lstadd_back(&strs, ft_lstnew(strdup("ccc")));
	ft_lstclear(&strs, free);
	/* 6 strdup content freed */ check(strs == NULL);
	showLeaks();

	write(1, "\n", 1);
	return (0);
}
