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
int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_lstnew\t: ")

	/* Standard pointer-as-content */
	t_list *l = ft_lstnew((void *)42);
	/* 1 content */ check(l && l->content == (void *)42);
	/* 2 next is NULL */ check(l && l->next == 0);
	/* 3 size matches */ mcheck(l, sizeof(t_list)); free(l); showLeaks();

	/* NULL content */
	l = ft_lstnew(NULL);
	/* 4 NULL content */ check(l && l->content == NULL);
	/* 5 next NULL */ check(l && l->next == NULL); free(l); showLeaks();

	/* String content */
	char *str = strdup("Tripouille");
	l = ft_lstnew(str);
	/* 6 string content */ check(l && l->content == str && !strcmp((char *)l->content, "Tripouille"));
	/* 7 next NULL */ check(l && l->next == NULL); free(str); free(l); showLeaks();

	/* Heap-allocated int content */
	int *n = (int *)malloc(sizeof(int)); *n = 42;
	l = ft_lstnew(n);
	/* 8 int* content */ check(l && l->content == n && *(int *)l->content == 42);
	free(n); free(l); showLeaks();

	/* Multiple sequential nodes are independent */
	t_list *a = ft_lstnew((void *)1);
	t_list *b = ft_lstnew((void *)2);
	/* 9 different nodes */ check(a && b && a != b && a->content == (void *)1 && b->content == (void *)2);
	/* 10 each has next=0 */ check(a->next == NULL && b->next == NULL);
	free(a); free(b); showLeaks();

	write(1, "\n", 1);
	return (0);
}
