#include "check.hpp"
#include "leaks.hpp"

extern int iTest;

void check(bool succes)
{
	if (succes)
		{std::ostringstream ss; ss << FG_GREEN << iTest++ << ".OK " << RESET_ALL; write(1, ss.str().c_str(), ss.str().size());}
	else
		{std::ostringstream ss; ss << FG_RED << iTest++ << ".KO " << RESET_ALL; write(1, ss.str().c_str(), ss.str().size());}
}

void mcheck(void * p, size_t required_size)
{
	/* Capacity is a lower bound; libc does not require an exact allocation size. */
	#ifdef __unix__
	if (required_size == 0 || (p && malloc_usable_size(p) >= required_size))
	#endif
	#ifdef __APPLE__
	if (required_size == 0 || (p && malloc_size(p) >= required_size))
	#endif
		{std::ostringstream ss; ss << FG_GREEN << iTest++ << ".MOK " << RESET_ALL; write(1, ss.str().c_str(), ss.str().size());}
	else
		{std::ostringstream ss; ss << FG_RED << iTest++ << ".MKO " << RESET_ALL; write(1, ss.str().c_str(), ss.str().size());}
}
