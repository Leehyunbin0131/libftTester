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
static void addOne(void *p) { ++*(int *)p; }
static int g_visits; static void visit(void *p) { (void)p; ++g_visits; }

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_lstiter\t: ")

	/* Increment each int in the list */
	int tab[] = {0, 1, 2, 3};
	t_list *l = ft_lstnew(tab);
	for (int i = 1; i < 4; ++i)
		ft_lstadd_back(&l, ft_lstnew(tab + i));
	ft_lstiter(l, addOne);
	t_list *tmp = l;
	/* 1..4 each incremented */
	for (int i = 0; i < 4; ++i) {
		check(*(int *)tmp->content == i + 1);
		tmp = (t_list *)tmp->next;
	}
	freeList(l); showLeaks();

	/* Empty list - must not crash */
	t_list *empty = NULL;
	g_visits = 0;
	ft_lstiter(empty, visit);
	/* 5 empty no visits */ check(g_visits == 0); showLeaks();

	/* Single node */
	int n = 100;
	t_list *one = ft_lstnew(&n);
	g_visits = 0;
	ft_lstiter(one, visit);
	/* 6 single visited once */ check(g_visits == 1);
	free(one); showLeaks();

	/* Many nodes - count visits */
	int data[20]; for (int i = 0; i < 20; ++i) data[i] = i;
	t_list *many = ft_lstnew(data);
	for (int i = 1; i < 20; ++i)
		ft_lstadd_back(&many, ft_lstnew(data + i));
	g_visits = 0;
	ft_lstiter(many, visit);
	/* 7 visits 20 nodes */ check(g_visits == 20);
	freeList(many); showLeaks();

	/* Apply twice: each int +2 */
	int t2[] = {10, 20, 30};
	t_list *l2 = ft_lstnew(t2);
	for (int i = 1; i < 3; ++i)
		ft_lstadd_back(&l2, ft_lstnew(t2 + i));
	ft_lstiter(l2, addOne);
	ft_lstiter(l2, addOne);
	/* 8 +2 to all */ check(t2[0] == 12 && t2[1] == 22 && t2[2] == 32);
	freeList(l2); showLeaks();

	write(1, "\n", 1);
	return (0);
}
