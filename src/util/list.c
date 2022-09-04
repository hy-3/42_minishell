#include "../minishell.h"

t_list *create_next_node(t_list *list, int count)
{
	if (count == 0)
	{
		list = (t_list *) malloc(sizeof(t_list));
		if (list == NULL)
			printf("malloc failed\n"); //TODO: error handle
		list->str = NULL;
		list->extra = NULL;
		list->next = NULL;
	}
	else
	{
		list->next = (t_list *) malloc(sizeof(t_list));
		if (list->next == NULL)
			printf("malloc failed\n"); //TODO: error handle
		list = list->next;
		list->str = NULL;
		list->extra = NULL;
		list->next = NULL;
	}
	return (list);
}

t_list *create_extra_node(t_list *list)
{
	list->extra = (t_list *) malloc(sizeof(t_list));
	if (list->extra == NULL)
		printf("malloc failed\n"); //TODO: error handle
	list = list->extra;
	list->str = NULL;
	list->extra = NULL;
	list->next = NULL;
	return (list);
}

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

int	is_nullstr_in_list(t_list *list)
{
	while (list != NULL)
	{
		if (list->str == NULL)
		{
			printf("parse error near `|'\n"); //TODO: error handle
			return (1);
		}
		list = list->next;
	}
	return (0);
}
