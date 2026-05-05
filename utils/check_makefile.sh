#!/bin/sh

set -u

LIBFT_PATH=${1:-..}
MAKEFILE="$LIBFT_PATH/Makefile"

red()
{
	tput setaf 1 2>/dev/null || true
}

green()
{
	tput setaf 2 2>/dev/null || true
}

reset()
{
	tput sgr0 2>/dev/null || true
}

fail()
{
	red
	printf "Makefile.KO: %s\n" "$1"
	reset
	exit 1
}

ok()
{
	green
	printf "Makefile.OK "
	reset
}

has_rule()
{
	awk -v rule="$1" '
		$0 ~ "^[[:space:]]*" rule "[[:space:]]*:" { found = 1 }
		END { exit(found ? 0 : 1) }
	' "$MAKEFILE"
}

has_source()
{
	awk -v src="$1" '
		index($0, src) { found = 1 }
		END { exit(found ? 0 : 1) }
	' "$MAKEFILE"
}

[ -f "$MAKEFILE" ] || fail "Makefile not found"

awk '
	/\$[({][[:space:]]*wildcard/ { bad = "wildcard function is forbidden" }
	/\*\.[co]/ { bad = "wildcard source/object pattern is forbidden" }
	/\$[({][[:space:]]*shell[[:space:]]+(ls|find)/ { bad = "shell ls/find source discovery is forbidden" }
	END {
		if (bad) {
			print bad
			exit 1
		}
	}
' "$MAKEFILE" >/tmp/libft_makefile_check.err 2>/dev/null \
	|| fail "$(sed -n '1p' /tmp/libft_makefile_check.err)"

awk '
	/^[[:space:]]*NAME[[:space:]]*[+:?]?=/ {
		if (index($0, "libft.a"))
			found = 1
	}
	END { exit(found ? 0 : 1) }
' "$MAKEFILE" || fail "NAME must be set to libft.a"

for rule in all clean fclean re
do
	has_rule "$rule" || fail "missing '$rule' rule"
done

SOURCES="ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c"

for src in $SOURCES
do
	[ -f "$LIBFT_PATH/$src" ] || fail "missing source file '$src'"
	has_source "$src" || fail "'$src' must be explicitly listed in Makefile"
done

ok
exit 0
