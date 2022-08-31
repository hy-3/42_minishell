#include "../minishell.h"

int	count_next_node(t_list *list)
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
