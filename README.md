# libftTester - 42 Gyeongsan
Enhanced tester for the libft project of 42 school, updated for Ubuntu 24.04 based 42 Gyeongsan systems.
This fork keeps the original Tripouille-style workflow, but adds broader edge-case coverage, Linux-safe leak tracking, and Makefile validation for common 42 subject requirements.
Clone this tester in your libft repository, or somewhere else and customize the path to your libft project by changing the LIBFT_PATH variable inside the Makefile.  

![alt text](https://i.imgur.com/EWmbpxx.png)  


## Commands
make m = launch all tests  
make a = same as make m (legacy alias)  
make [function name] = launch associated test ex: `make calloc`  
make checkmakefile = validate the libft Makefile only
 
make dockerm = launch all tests in linux container  
make dockera = same as make dockerm (legacy alias)  
make docker [function name] = launch associated test in linux container ex: `make dockercalloc`  
Thanks to gurival- for the docker idea (https://github.com/grouville/valgrind_42)  

make vs [function name] = open the corresponding tests in vscode ex: `make vscalloc`  

Note: Bonus-only targets were removed because list functions are now part of mandatory libft.  


## Additional checks in this fork
- Broader tests for valid character inputs, signed/unsigned byte behavior, zero-length operations with valid pointers, allocation capacity, file descriptor output, and list edge cases.
- Linux/WSL-safe leak tracker guard to avoid recursive malloc-hook crashes on Ubuntu-based environments.
- Makefile validation before tests:
  - Makefile must exist.
  - `NAME` must be set to `libft.a`.
  - `all`, `clean`, `fclean`, and `re` rules must exist.
  - `$(wildcard ...)`, `*.c`, `*.o`, and shell-based source discovery with `ls`/`find` are rejected.
  - Mandatory libft source files must exist and be explicitly listed in the Makefile.

## Defined-behavior policy

Libc replacements are tested only within their documented input domains. A result observed from undefined behavior on one libc is not a required result for libft.

- `memcpy` and `memmove` receive valid pointers even when the length is zero. NULL-pointer handling is not required.
- `isalpha`, `isdigit`, `isalnum`, `isprint`, `toupper`, and `tolower` are compared with libc in the initial C locale over `0..UCHAR_MAX`, plus `EOF`. Other integer inputs are excluded. Boolean results are compared by truth value, not an exact nonzero value. `isascii` is a separate extension whose contract accepts any `int`.
- `atoi` is tested only when the converted value fits in `int`. Overflow results and `errno` are not graded; `INT_MIN` and `INT_MAX` remain covered.
- Zero-size `calloc` may return NULL or a pointer that can be freed. The result is never dereferenced. Products that cannot fit in `size_t` must fail instead of allocating a wrapped size. Huge but representable requests are not required to fail merely because they fail on one machine.
- Allocation checks require at least the requested capacity, not an exact allocator size class. Valgrind remains responsible for detecting invalid accesses and frees; allocator usable-size diagnostics do not prove the original requested size.
- `strlcpy`, `strlcat`, `strnstr`, `bzero`, and `isascii` follow their documented POSIX/BSD contracts. Destination-size arguments describe real buffer capacity. Large search limits for NUL-terminated strings remain valid.
- Additional 42 functions (`ft_substr`, `ft_split`, list functions, and others) have no libc equivalent and keep their project-specific tests. Empty lists and NULL list content remain covered; passing NULL instead of a new node to `ft_lstadd_back` is not required. Makefile checks are project checks, not C standard requirements.

References: [C11 committee draft N1570](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf), sections 7.4, 7.22.1, 7.22.3, and 7.24.1; [strlcpy/strlcat](https://man.openbsd.org/strlcpy); [strnstr](https://man.freebsd.org/cgi/man.cgi?query=strnstr&sektion=3); [isascii](https://man.openbsd.org/isascii.3).

## Tester self-check

Run `python3 utils/selftest.py` without a student libft. It compiles the 23 libc/POSIX/BSD test programs against the system libraries, guards the ctype/atoi/memory-copy input domains and destination capacities, and also tests NULL-returning zero-size allocations and oversized allocations. A separate check verifies that insufficient capacity is still rejected. It exits nonzero on compilation errors, crashes, or unexpected KO output. Build artifacts live in a temporary directory.

Requires Python 3, a C/C++ compiler, and the libbsd runtime on Linux (`libbsd.so.0`, for `strnstr`). `CC` and `CXX` select compilers. To check memory accesses too:

```sh
RUNNER='valgrind -q --leak-check=full --error-exitcode=99' python3 utils/selftest.py
```


## Setup docker in goinfre for 42 mac  
```sh
rm -rf ~/Library/Containers/com.docker.docker  
rm -rf ~/.docker  
rm -rf /goinfre/${USER}/docker /goinfre/${USER}/agent  
mkdir -p /goinfre/${USER}/docker /goinfre/${USER}/agent  
ln -s /goinfre/${USER}/agent ~/Library/Containers/com.docker.docker  
ln -s /goinfre/${USER}/docker ~/.docker 
```


## Outputs
![alt text](https://i.imgur.com/en8rJpS.png)  
![alt text](https://i.imgur.com/ZvzhIoZ.png)  
![alt text](https://i.imgur.com/KrlN2Pg.png)  

MOK / MKO = allocator capacity diagnostic: at least the required bytes must be available; larger allocations are accepted. A zero-byte requirement accepts NULL as well. This is not an exact malloc-size requirement.


## Report bugs / Improvement
Contact me on slack or discord : jgambard  
