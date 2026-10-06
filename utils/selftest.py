#!/usr/bin/env python3
"""Run the libc-facing tests against libc and permitted allocation variants."""
import ctypes.util
import os
from pathlib import Path
import re
import shlex
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parent.parent
PROTOTYPES = {
    "memset": ("void *", "void *p, int c, size_t n", "p, c, n"),
    "bzero": ("void", "void *p, size_t n", "p, n"),
    "memcpy": ("void *", "void *d, const void *s, size_t n", "d, s, n"),
    "memmove": ("void *", "void *d, const void *s, size_t n", "d, s, n"),
    "memchr": ("void *", "const void *p, int c, size_t n", "p, c, n"),
    "memcmp": ("int", "const void *a, const void *b, size_t n", "a, b, n"),
    "strlen": ("size_t", "const char *s", "s"),
    **{name: ("int", "int c", "c") for name in
       ("isalpha", "isdigit", "isalnum", "isascii", "isprint", "toupper", "tolower")},
    "strchr": ("char *", "const char *s, int c", "s, c"),
    "strrchr": ("char *", "const char *s, int c", "s, c"),
    "strncmp": ("int", "const char *a, const char *b, size_t n", "a, b, n"),
    "strlcpy": ("size_t", "char *d, const char *s, size_t n", "d, s, n"),
    "strlcat": ("size_t", "char *d, const char *s, size_t n", "d, s, n"),
    "strnstr": ("char *", "const char *s, const char *needle, size_t n", "s, needle, n"),
    "atoi": ("int", "const char *s", "s"),
    "calloc": ("void *", "size_t n, size_t size", "n, size"),
    "strdup": ("char *", "const char *s", "s"),
}

GUARDS = {
    name: "assert(c == EOF || (c >= 0 && c <= UCHAR_MAX));"
    for name in ("isalpha", "isdigit", "isalnum", "isprint", "toupper", "tolower")
}
GUARDS.update({
    "memcpy": "assert(d && s);",
    "memmove": "assert(d && s);",
    "atoi": "assert(s); long v = strtol(s, NULL, 10); assert(v >= INT_MIN && v <= INT_MAX);",
})
VARIANTS = {
    "calloc": """
        if (getenv("SELFTEST_ALTERNATIVE")) {
            if (!n || !size || size > SIZE_MAX / n) return NULL;
            assert(n * size <= SIZE_MAX - 64);
            return calloc(1, n * size + 64);
        }
    """,
    "strdup": """
        if (getenv("SELFTEST_ALTERNATIVE")) {
            char *p = malloc(strlen(s) + 65);
            assert(p);
            return memcpy(p, s, strlen(s) + 1);
        }
    """,
}


def main():
    cc = shlex.split(os.environ.get("CC", "cc"))
    cxx = shlex.split(os.environ.get("CXX", "c++"))
    runner = shlex.split(os.environ.get("RUNNER", ""))
    bsd = []
    if sys.platform.startswith("linux"):
        library = ctypes.util.find_library("bsd")
        if not library:
            sys.exit("selftest requires the libbsd runtime for strnstr on Linux")
        bsd = ["-l:" + library]

    with tempfile.TemporaryDirectory(prefix="libft-selftest-") as directory:
        tmp = Path(directory)
        header = "#include <stddef.h>\n#include <assert.h>\n"
        source = """
            #include <assert.h>
            #include <ctype.h>
            #include <limits.h>
            #include <stdint.h>
            #include <stdio.h>
            #include <stdlib.h>
            #include <string.h>
            #include <strings.h>
            size_t strlcpy(char *, const char *, size_t);
            size_t strlcat(char *, const char *, size_t);
            char *strnstr(const char *, const char *, size_t);
        """
        for name, (result, params, args) in PROTOTYPES.items():
            declaration = f"{result} ft_{name}({params})"
            header += declaration + ";\n"
            ret = "" if result == "void" else "return "
            source += (declaration + " { " + GUARDS.get(name, "")
                       + VARIANTS.get(name, "") + f"{ret}{name}({args}); }}\n")
        # Check destination capacities at the call site, where array sizes are known.
        for name in ("strlcpy", "strlcat"):
            header += (f"#define ft_{name}(d,s,n) "
                       f"(assert((size_t)(n) <= __builtin_object_size(d, 0)), "
                       f"ft_{name}((d),(s),(n)))\n")
        (tmp / "libft.h").write_text(header)
        (tmp / "reference.c").write_text(source)
        subprocess.run(cc + ["-g", "-c", str(tmp / "reference.c"), "-o", str(tmp / "reference.o")], check=True)
        flags = ["-g", "-std=c++11", "-I" + str(ROOT / "utils"), "-I" + directory]
        objects = [str(tmp / "reference.o")]
        for name in ("check", "color", "sigsegv", "leaks"):
            obj = str(tmp / (name + ".o"))
            subprocess.run(cxx + flags + ["-c", str(ROOT / "utils" / (name + ".cpp")), "-o", obj], check=True)
            objects.append(obj)
        failures = []
        for name in PROTOTYPES:
            binary = str(tmp / name)
            subprocess.run(cxx + flags + [str(ROOT / "tests" / f"ft_{name}_test.cpp")]
                           + objects + bsd + ["-ldl", "-o", binary], check=True)
            for alternative in (False, True) if name in VARIANTS else (False,):
                env = dict(os.environ)
                env.pop("SELFTEST_ALTERNATIVE", None)
                if alternative:
                    env["SELFTEST_ALTERNATIVE"] = "1"
                result = subprocess.run(runner + [binary], cwd=tmp, env=env,
                                        capture_output=True, text=True, timeout=30)
                label = name + (" (NULL zero-size / extra capacity)" if alternative else " (libc)")
                output = result.stdout + result.stderr
                failed = result.returncode != 0 or re.search(r"(?:KO|SIGSEGV|runtime error:)", output)
                print(f"{label}: {'FAIL' if failed else 'PASS'}", flush=True)
                if failed:
                    failures.append(label)
                    print(output, flush=True)
        if failures:
            sys.exit(f"{len(failures)} self-check(s) failed")
        # Larger allocations pass, but missing/insufficient storage still fails.
        (tmp / "capacity.cpp").write_text('''
            #include "check.hpp"
            #include "leaks.hpp"
            int iTest = 1;
            int main() {
                void *p = malloc(128);
                mcheck(p, 16); mcheck(p, 4096);
                mcheck(NULL, 0); mcheck(NULL, 1);
                free(p); showLeaks();
            }
        ''')
        binary = str(tmp / "capacity")
        subprocess.run(cxx + flags + [str(tmp / "capacity.cpp")] + objects
                       + bsd + ["-ldl", "-o", binary], check=True)
        result = subprocess.run(runner + [binary], cwd=tmp, capture_output=True, text=True, timeout=30)
        if (result.returncode != 0 or "LEAKS.KO" in result.stdout
                or re.findall(r"\d+\.(MOK|MKO)", result.stdout) != ["MOK", "MKO", "MOK", "MKO"]):
            sys.exit("Capacity self-check failed:\n" + result.stdout + result.stderr)
        print("Allocation capacity positive/negative checks: PASS")
        print("All libc self-checks passed.")


if __name__ == "__main__":
    main()
