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
	struct s_imput	*extra;
}	t_imput;

void	parse(char *original_imput, t_imput *parsed_imput);
void	cust_split(char const *s, char c, t_imput *parsed_imput);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *str);

#endif