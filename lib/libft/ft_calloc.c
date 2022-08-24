/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:35:11 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/19 16:50:54 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates [count] objects which are [size] bytes to memory.
 * 
 * @param count(size_t): Number of objects
 * @param size(size_t): Byte sizes.
 * @return (void *): Pointer to allocated memory.
 */
void	*ft_calloc(size_t count, size_t size)
{
	void	*res;

	if (size != 0)
		if (count > SIZE_MAX / size)
			return (NULL);
	res = (void *) malloc(count * size);
	if (res == NULL)
		return (NULL);
	ft_bzero(res, count * size);
	return (res);
}
