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
#include <climits>

static int writeAndRead(int n, char *out, int outSize)
{
	int fd = open("tripouille", O_RDWR | O_CREAT | O_TRUNC, 0777);
	ft_putnbr_fd(n, fd);
	lseek(fd, 0, SEEK_SET);
	int r = read(fd, out, outSize);
	out[r] = 0;
	close(fd);
	unlink("./tripouille");
	return r;
}

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_putnbr_fd\t: ")

	char s[42];

	/* 0 */
	memset(s, 0, 42);
	writeAndRead(0, s, 41);
	/* 1 zero */ check(!strcmp(s, "0")); showLeaks();

	/* Positive multi-digit */
	memset(s, 0, 42);
	writeAndRead(10, s, 41);
	/* 2 ten */ check(!strcmp(s, "10")); showLeaks();

	/* INT_MAX */
	memset(s, 0, 42);
	writeAndRead(INT_MAX, s, 41);
	/* 3 INT_MAX */ check(!strcmp(s, to_string(INT_MAX).c_str())); showLeaks();

	/* INT_MIN */
	memset(s, 0, 42);
	writeAndRead(INT_MIN, s, 41);
	/* 4 INT_MIN */ check(!strcmp(s, to_string(INT_MIN).c_str())); showLeaks();

	/* Negative */
	memset(s, 0, 42);
	writeAndRead(-42, s, 41);
	/* 5 -42 */ check(!strcmp(s, "-42")); showLeaks();

	/* Single digit positive */
	memset(s, 0, 42);
	writeAndRead(7, s, 41);
	/* 6 single digit */ check(!strcmp(s, "7")); showLeaks();

	/* Single digit negative */
	memset(s, 0, 42);
	writeAndRead(-7, s, 41);
	/* 7 single digit neg */ check(!strcmp(s, "-7")); showLeaks();

	/* All single digits */
	int ok = 1;
	for (int i = 0; i < 10; ++i) {
		memset(s, 0, 42);
		writeAndRead(i, s, 41);
		char ref[2] = {(char)('0' + i), 0};
		if (strcmp(s, ref)) ok = 0;
	}
	/* 8 all single digits */ check(ok); showLeaks();

	/* Numbers near boundaries */
	memset(s, 0, 42);
	writeAndRead(INT_MAX - 1, s, 41);
	/* 9 INT_MAX-1 */ check(!strcmp(s, to_string(INT_MAX - 1).c_str())); showLeaks();

	memset(s, 0, 42);
	writeAndRead(INT_MIN + 1, s, 41);
	/* 10 INT_MIN+1 */ check(!strcmp(s, to_string(INT_MIN + 1).c_str())); showLeaks();

	/* Sequential output */
	int fd = open("tripouille", O_RDWR | O_CREAT | O_TRUNC, 0777);
	ft_putnbr_fd(1, fd);
	ft_putnbr_fd(2, fd);
	ft_putnbr_fd(3, fd);
	lseek(fd, 0, SEEK_SET);
	memset(s, 0, 42); int r = read(fd, s, 41);
	close(fd); unlink("./tripouille");
	/* 11 sequential */ check(r == 3 && !strcmp(s, "123")); showLeaks();

	/* Larger random sample vs to_string */
	int values[] = {42, -42, 100, -100, 1000000, -1000000, 99999, -99999};
	ok = 1;
	for (size_t i = 0; i < sizeof(values)/sizeof(values[0]); ++i) {
		memset(s, 0, 42);
		writeAndRead(values[i], s, 41);
		if (strcmp(s, to_string(values[i]).c_str())) ok = 0;
	}
	/* 12 random sample */ check(ok); showLeaks();

	write(1, "\n", 1);
	return (0);
}
