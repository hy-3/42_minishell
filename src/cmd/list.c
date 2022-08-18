#include "../minishell.h"

void	list_iter(t_list *list, t_env_param *env_p, int num_of_args, void (*f)(char *str, t_env_param *env_p, int i, int num_of_args))
{
	int	i;

	i = 0;
	while (list != NULL)
	{
		f(list->str, env_p, i, num_of_args);
		list = list->next;
		i++;
	}
}
