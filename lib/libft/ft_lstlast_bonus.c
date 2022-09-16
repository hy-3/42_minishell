/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 13:51:00 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/19 13:51:02 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Return a last node of list[lst].
 * 
 * @param lst(t_list **): Source list.
 * @return (t_list *): Pointer of last node.
 */
t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current_node;
	t_list	*current_next;

	if (lst == NULL)
		return (NULL);
	current_node = lst;
	current_next = lst->next;
	while (current_next != NULL)
	{
		current_node = current_next;
		current_next = current_next->next;
	}
	return (current_node);
}
