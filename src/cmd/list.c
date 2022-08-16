#include "../minishell.h"

int	cust_lstsize(t_imput **lst)
{
	int		count;
	t_imput	*current;

	if (*lst == NULL)
		return (0);
	count = 1;
	current = (*lst)->next;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	lstiter_exec_cmd(t_imput **lst, t_env_param *env_p, int num_of_args, void (*f)(char *str, t_env_param *env_p, int i, int num_of_args))
{
	int	i;

	i = 0;
	while (*lst != NULL)
	{
		f((*lst)->str, env_p, i, num_of_args);
		(*lst) = (*lst)->next;
		i++;
	}
}
