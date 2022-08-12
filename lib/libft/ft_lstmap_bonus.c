/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 13:51:12 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/19 13:51:14 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Apply funtion[f] to contents of nodes in given list[lst].
 * 
 * @param lst(t_list **): Source list.
 * @param f(void *(void *)): Pointer to function to apply to content of node.
 * @param del(void *(void *)): Pointer to function to delete content of node.
 * @return (t_list *): New list after function is applied to content of node.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*old;
	t_list	*new;
	t_list	*res;
	int		count;

	count = 0;
	old = NULL;
	new = NULL;
	res = NULL;
	if (lst == NULL)
		return (NULL);
	while (lst != NULL)
	{
		old = new;
		new = ft_lstnew(f(lst->content));
		if (new == NULL)
			del(new->content);
		if (count++ == 0)
			res = new;
		else
			old->next = new;
		lst = lst->next;
	}
	new->next = NULL;
	return (res);
}
