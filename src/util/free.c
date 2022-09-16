#include "../minishell.h"

void	free_list(t_list *list)
{
	t_list	*ex;

	while (list != NULL)
	{
		if (list->str != NULL)
			free(list->str);
		ex = list->extra;
		while (ex != NULL)
		{
			if (ex->str != NULL)
				free(ex->str);
			free(ex);
			ex = ex->extra;
		}
		free(list);
		list = list->next;
	}
}