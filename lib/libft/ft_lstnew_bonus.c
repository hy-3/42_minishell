/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 13:51:22 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/19 13:51:24 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Create a new node with [content].
 * 
 * @param content(void *): Content to be added in a node.
 * @return (t_list *): Pointer to be created new node.
 */
t_list	*ft_lstnew(void *content)
{
	t_list	*res;

	res = NULL;
	res = (t_list *) malloc(sizeof(t_list));
	if (res == NULL)
		return (NULL);
	res->content = content;
	res->next = NULL;
	return (res);
}
