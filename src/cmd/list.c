#include "../minishell.h"

void	list_iter(t_list *list, t_env_param *env_p, int list_size, void (*f)(char *str, t_env_param *env_p, int i, int list_size))
{
	int	i;

	i = 0;
	while (list != NULL)
	{
		f(list->str, env_p, i, list_size);
		list = list->next;
		i++;
	}
}
