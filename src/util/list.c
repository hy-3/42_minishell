/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:05:54 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/09/19 19:12:41 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*create_next_node(t_list *list, int count)
{
	if (count == 0)
	{
		list = (t_list *) malloc(sizeof(t_list));
		if (list == NULL)
			cust_write("malloc failed\n", 1);
		list->str = NULL;
		list->extra = NULL;
		list->next = NULL;
	}
	else
	{
		list->next = (t_list *) malloc(sizeof(t_list));
		if (list->next == NULL)
			cust_write("malloc failed\n", 1);
		list = list->next;
		list->str = NULL;
		list->extra = NULL;
		list->next = NULL;
	}
	return (list);
}

t_list	*create_extra_node(t_list *list)
{
	list->extra = (t_list *) malloc(sizeof(t_list));
	if (list->extra == NULL)
		cust_write("malloc failed\n", 1);
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

int	is_nullstr_in_list(t_list *list, t_env *env)
{
	t_list	*first_node;

	first_node = list;
	while (list != NULL)
	{
		if (list->str == NULL)
		{
			printf("parse error near `|'\n");
			env->status_code = 258;
			free_list(first_node);
			return (1);
		}
		list = list->next;
	}
	return (0);
}

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
