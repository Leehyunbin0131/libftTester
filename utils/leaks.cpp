#include "leaks.hpp"

#ifdef __linux__
extern "C" void *__libc_malloc(size_t size);
extern "C" void __libc_free(void *p);
#endif

std::vector<ptr> mallocList;
static bool g_in_malloc_hook = false;
static void *(*g_libc_malloc)(size_t) = NULL;
static void (*g_libc_free)(void *) = NULL;

bool operator==(ptr const & p1, ptr const & p2)
{
    return (p1.p == p2.p);
}

#ifdef __APPLE__
void * malloc(size_t size)
#endif
#ifdef __unix__
void * malloc(size_t size) throw()
#endif
{
    if (g_libc_malloc == NULL)
    {
        if (g_in_malloc_hook)
        {
#ifdef __linux__
            return (__libc_malloc(size));
#else
            return (NULL);
#endif
        }
        g_in_malloc_hook = true;
        g_libc_malloc = (void *(*)(size_t))dlsym(RTLD_NEXT, "malloc");
        g_in_malloc_hook = false;
    }
    void * p = g_libc_malloc(size);
    if (p != NULL && !g_in_malloc_hook)
    {
        g_in_malloc_hook = true;
        mallocListAdd(p, size);
        g_in_malloc_hook = false;
    }
    return (p);
}

#ifdef __APPLE__
void free(void * p)
#endif
#ifdef __unix__
void free(void * p) throw()
#endif
{
    if (g_libc_free == NULL)
    {
        if (g_in_malloc_hook)
        {
#ifdef __linux__
            __libc_free(p);
#endif
            return ;
        }
        g_in_malloc_hook = true;
        g_libc_free = (void (*)(void *))dlsym(RTLD_NEXT, "free");
        g_in_malloc_hook = false;
    }
    g_libc_free(p);
    if (p != NULL && !g_in_malloc_hook)
    {
        g_in_malloc_hook = true;
        mallocListRemove(p);
        g_in_malloc_hook = false;
    }
}

void mallocListAdd(void * p, size_t size)
{
    mallocList.push_back(ptr(p, size));
}

void mallocListRemove(void * p)
{
    std::vector<ptr>::iterator it = find(mallocList.begin(), mallocList.end(), ptr(p));
    if (it != mallocList.end())
        mallocList.erase(it);
}

void showLeaks(void)
{
    if (mallocList.size() != 0)
    {
        std::ostringstream ss; ss << FG_RED << "LEAKS.KO " << RESET_ALL; write(1, ss.str().c_str(), ss.str().size());
        std::vector<ptr>::iterator it = mallocList.begin(); std::vector<ptr>::iterator ite = mallocList.end();
        for (; it != ite; ++it)
            {std::ostringstream ss; ss << "[" << it->p << " : " << it->size << "] "; write(1, ss.str().c_str(), ss.str().size());}
    }
    mallocList.clear();
}
