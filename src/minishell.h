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

t_imput	*parse(char *original_imput);
t_imput	*cust_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);

#endif