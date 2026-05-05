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
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

static int writeAndRead(const char *str, char *out, int outSize)
{
	int fd = open("tripouille", O_RDWR | O_CREAT | O_TRUNC, 0777);
	ft_putendl_fd((char *)str, fd);
	lseek(fd, 0, SEEK_SET);
	int n = read(fd, out, outSize);
	close(fd);
	unlink("./tripouille");
	return n;
}

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_putendl_fd\t: ")

	char s[100];

	/* Basic */
	memset(s, 0, 100);
	int n = writeAndRead("42", s, 50);
	/* 1 "42\n" */ check(n == 3 && !strcmp(s, "42\n")); showLeaks();

	/* Empty must still write the newline */
	memset(s, 0, 100);
	n = writeAndRead("", s, 50);
	/* 2 just newline */ check(n == 1 && s[0] == '\n'); showLeaks();

	/* Long string */
	memset(s, 0, 100);
	n = writeAndRead("Tripouille", s, 50);
	/* 3 long + newline */ check(n == 11 && !strcmp(s, "Tripouille\n")); showLeaks();

	/* Special chars */
	memset(s, 0, 100);
	n = writeAndRead("a\tb", s, 50);
	/* 4 tab + newline */ check(n == 4 && !strcmp(s, "a\tb\n")); showLeaks();

	/* Multiple sequential calls add multiple newlines */
	int fd = open("tripouille", O_RDWR | O_CREAT | O_TRUNC, 0777);
	ft_putendl_fd((char *)"hi", fd);
	ft_putendl_fd((char *)"42", fd);
	lseek(fd, 0, SEEK_SET);
	memset(s, 0, 100); n = read(fd, s, 50);
	close(fd); unlink("./tripouille");
	/* 5 sequential lines */ check(n == 6 && !strcmp(s, "hi\n42\n")); showLeaks();

	/* Heap allocation */
	char *h = strdup("hello");
	memset(s, 0, 100);
	n = writeAndRead(h, s, 50);
	free(h);
	/* 6 heap input */ check(n == 6 && !strcmp(s, "hello\n")); showLeaks();

	write(1, "\n", 1);
	return (0);
}
