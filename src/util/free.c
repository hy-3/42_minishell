#include "../minishell.h"

void	free_list(t_list *list)
{
	t_list	*ex;

	while (list != NULL)
	{
		if (list->str != NULL)
			free(list->str);
		while (ex != NULL)
		{
			if (ex->str != NULL)
				free(ex->str);
			ex = ex->extra;
		}
		list = list->next;
	}
}