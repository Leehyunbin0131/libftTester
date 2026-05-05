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
	ft_putstr_fd((char *)str, fd);
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
	title("ft_putstr_fd\t: ")

	char s[100];

	/* Basic string */
	memset(s, 0, 100);
	int n = writeAndRead("42", s, 10);
	/* 1 "42" */ check(n == 2 && !strcmp(s, "42")); showLeaks();

	/* Longer string */
	memset(s, 0, 100);
	n = writeAndRead("Tripouille", s, 50);
	/* 2 long word */ check(n == 10 && !strcmp(s, "Tripouille")); showLeaks();

	/* Empty string writes nothing */
	memset(s, 'A', 100); s[5] = 0;
	int fd = open("tripouille", O_RDWR | O_CREAT | O_TRUNC, 0777);
	ft_putstr_fd((char *)"", fd);
	struct stat st; fstat(fd, &st);
	close(fd); unlink("./tripouille");
	/* 3 empty -> 0 bytes */ check(st.st_size == 0); showLeaks();

	/* String with special chars */
	memset(s, 0, 100);
	n = writeAndRead("Hello\nWorld\t!", s, 50);
	/* 4 special */ check(n == 13 && !strcmp(s, "Hello\nWorld\t!")); showLeaks();

	/* String with spaces */
	memset(s, 0, 100);
	n = writeAndRead("a b c d e", s, 50);
	/* 5 spaces */ check(n == 9 && !strcmp(s, "a b c d e")); showLeaks();

	/* Heap string */
	char *h = strdup("on the heap");
	memset(s, 0, 100);
	n = writeAndRead(h, s, 50);
	free(h);
	/* 6 heap str */ check(n == 11 && !strcmp(s, "on the heap")); showLeaks();

	/* Multiple sequential calls */
	fd = open("tripouille", O_RDWR | O_CREAT | O_TRUNC, 0777);
	ft_putstr_fd((char *)"abc", fd);
	ft_putstr_fd((char *)"def", fd);
	ft_putstr_fd((char *)"42", fd);
	lseek(fd, 0, SEEK_SET);
	memset(s, 0, 100); n = read(fd, s, 50);
	close(fd); unlink("./tripouille");
	/* 7 sequential */ check(n == 8 && !strcmp(s, "abcdef42")); showLeaks();

	write(1, "\n", 1);
	return (0);
}
