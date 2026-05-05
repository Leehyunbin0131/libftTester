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

int g_delCount;

static void countingDel(void *p) { ++g_delCount; free(p); }
static void noopDel(void *p) { (void)p; ++g_delCount; }

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_lstdelone\t: ");

	/* Standard delete */
	t_list *l = ft_lstnew(malloc(1));
	g_delCount = 0;
	ft_lstdelone(l, countingDel);
	/* 1 del called once */ check(g_delCount == 1);
	showLeaks();

	/* del should be applied to content but not to .next */
	t_list *node = ft_lstnew((void *)0x1234);
	t_list *next = ft_lstnew((void *)0x5678);
	node->next = next;
	g_delCount = 0;
	ft_lstdelone(node, noopDel);
	/* 2 only one del call (next not freed) */ check(g_delCount == 1);
	/* 3 next still valid (not freed) */ check(next->content == (void *)0x5678);
	free(next); showLeaks();

	/* Delete a node with NULL content */
	t_list *nl = ft_lstnew(NULL);
	g_delCount = 0;
	ft_lstdelone(nl, noopDel);
	/* 4 NULL content - del still called */ check(g_delCount == 1);
	showLeaks();

	/* Heap content properly freed */
	char *str = strdup("hello");
	t_list *sl = ft_lstnew(str);
	ft_lstdelone(sl, free); /* str freed inside */
	/* 5 heap content freed */ check(1); /* valgrind enforces no leak */
	showLeaks();

	write(1, "\n", 1);
	return (0);
}
