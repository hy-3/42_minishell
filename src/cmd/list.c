#include "../minishell.h"

int	cust_lstsize(t_imput **lst)
{
	int		count;
	t_imput	*current;

	if (*lst == NULL)
		return (0);
	count = 1;
	printf("$$ first: s:%s, p:%p\n", (*lst)->str, (*lst)->str);
	printf("$$ second: s:%s, p:%p\n", (*lst)->next->str, (*lst)->next->str);
	// current = (*lst)->next;
	current = (*lst);
	while (current)
	{
		printf("looppppp");
		count++;
		current = current->next;
		// printf("$ str: %p, %s\n", (current)->str, (current)->str);
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
