#include "../minishell.h"

void	cust_perror(char *str, int status)
{
	perror(str);
	exit(status);
}

void	cust_write(char *str, int status)
{
	int	n;

	n = ft_strlen(str);
	write(2, str, n);
	exit(status);
}
