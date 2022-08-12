/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 13:51:32 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/19 13:51:34 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Count the number of nodes in a list[lst].
 * 
 * @param lst(t_list *): Source list.
 * @return (int): The number of nodes in a list.
 */
int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*current_position;

	if (lst == NULL)
		return (0);
	count = 1;
	current_position = lst->next;
	while (current_position != NULL)
	{
		count++;
		current_position = current_position->next;
	}
	return (count);
}
