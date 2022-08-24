/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 13:50:14 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/19 13:50:17 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Delete all nodes in a list[lst].
 * 
 * @param lst(t_list **): Source list.
 * @param del(void *(void *)): Pointer of function to delete a content of node.
 * @return (void)
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current_addr;
	t_list	*current_next;

	current_addr = *lst;
	while (current_addr != NULL)
	{
		current_next = current_addr->next;
		del(current_addr->content);
		free(current_addr);
		current_addr = current_next;
	}
	*lst = NULL;
}
