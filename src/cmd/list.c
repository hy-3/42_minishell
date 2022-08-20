#include "../minishell.h"

void	list_iter(t_list *list, t_env_param *env_p, int num_node_hor, void (*f)(t_list *list, t_env_param *env_p, int i, int num_node_hor))
{
	int	i;

	i = 0;
	while (list != NULL)
	{
		f(list, env_p, i, num_node_hor);
		list = list->next;
		i++;
	}
}

int	count_next(t_list *list)
{
	t_list	*prev_node;
	int		list_size;

	list_size = 0;
	while (list != NULL)
	{
		prev_node = list;
		list = list->next;
		list_size++;
	}
	return (list_size);
}

int	count_extra(t_list *list)
{
	t_list	*prev_node;
	int		list_size;

	list_size = 0;
	while (list != NULL)
	{
		prev_node = list;
		list = list->extra;
		list_size++;
	}
	return (list_size);
}
