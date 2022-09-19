/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:05:48 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/09/19 17:05:50 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
