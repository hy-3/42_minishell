#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"

typedef struct s_imput
{
	char			*str;
	struct s_imput	*next;
}	t_imput;

//	src/parse/parse.c
t_imput	*parse(char *original_imput);
//	src/parse/str_split.c
t_imput	*cust_split(char const *s, char c);
//	Libft
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

#endif