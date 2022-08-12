/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 13:49:27 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/19 13:49:43 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Add a new node[new] to end of the list[lst].
 * 
 * @param lst(t_list **): Source list.
 * @param new(t_list *): Node to be added.
 * @return (void)
 */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current_node;
	t_list	*current_next;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current_node = (*lst);
	current_next = (*lst)->next;
	while (current_next != NULL)
	{
		current_node = current_next;
		current_next = current_next->next;
	}
	current_node->next = new;
}
