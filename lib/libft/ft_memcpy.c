/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:37:02 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/19 11:17:06 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copy [n] bytes from [src] to [dst].
 * 
 * @param dst(void *): Pointer to destination memory area.
 * @param src(const void *): Pointer to source memory area.
 * @param n(size_t): Number of bytes to copy.
 * @return (void *): The original value of [dst].
 */
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*tmp_dst;
	const unsigned char	*tmp_src;

	if (n == 0 || dst == src)
		return (dst);
	tmp_dst = (unsigned char *) dst;
	tmp_src = (const unsigned char *) src;
	while (n > 0)
	{
		*tmp_dst++ = *tmp_src++;
		n--;
	}
	return (dst);
}
