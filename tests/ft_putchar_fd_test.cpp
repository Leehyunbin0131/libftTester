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

static int writeAndRead(char c, char *out)
{
	int fd = open("tripouille", O_RDWR | O_CREAT | O_TRUNC, 0777);
	ft_putchar_fd(c, fd);
	lseek(fd, 0, SEEK_SET);
	int n = read(fd, out, 4);
	close(fd);
	unlink("./tripouille");
	return n;
}

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_putchar_fd\t: ")

	char s[10];

	/* Standard char */
	memset(s, 0, 10);
	int n = writeAndRead('a', s);
	/* 1 single 'a' */ check(n == 1 && s[0] == 'a' && s[1] == 0); showLeaks();

	/* Different char */
	memset(s, 0, 10);
	n = writeAndRead('Z', s);
	/* 2 'Z' */ check(n == 1 && s[0] == 'Z'); showLeaks();

	/* Digit */
	memset(s, 0, 10);
	n = writeAndRead('7', s);
	/* 3 digit */ check(n == 1 && s[0] == '7'); showLeaks();

	/* Special char (newline) */
	memset(s, 0, 10);
	n = writeAndRead('\n', s);
	/* 4 newline */ check(n == 1 && s[0] == '\n'); showLeaks();

	/* Tab */
	memset(s, 0, 10);
	n = writeAndRead('\t', s);
	/* 5 tab */ check(n == 1 && s[0] == '\t'); showLeaks();

	/* Null byte must still be written */
	memset(s, 'A', 10);
	int fd = open("tripouille", O_RDWR | O_CREAT | O_TRUNC, 0777);
	ft_putchar_fd(0, fd);
	lseek(fd, 0, SEEK_SET);
	n = read(fd, s, 4);
	close(fd); unlink("./tripouille");
	/* 6 null byte */ check(n == 1 && s[0] == 0); showLeaks();

	/* Multiple sequential writes */
	fd = open("tripouille", O_RDWR | O_CREAT | O_TRUNC, 0777);
	ft_putchar_fd('4', fd);
	ft_putchar_fd('2', fd);
	ft_putchar_fd('!', fd);
	lseek(fd, 0, SEEK_SET);
	memset(s, 0, 10); n = read(fd, s, 5);
	close(fd); unlink("./tripouille");
	/* 7 sequential */ check(n == 3 && !strcmp(s, "42!")); showLeaks();

	/* High byte */
	memset(s, 0, 10);
	n = writeAndRead((char)0x80, s);
	/* 8 high byte */ check(n == 1 && (unsigned char)s[0] == 0x80); showLeaks();

	write(1, "\n", 1);
	return (0);
}
