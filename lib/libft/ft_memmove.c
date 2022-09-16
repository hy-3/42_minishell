/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:37:10 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/19 11:23:49 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copy [len] bytes from [src] to [dst].
 * it is safer than memcpy when [src] and [dst] memory areas are overlapped.
 *
 * @param dst(void *): Pointer to destination memory area.
 * @param src(const void *): Pointer to source memory area.
 * @param len(size_t): Number of bytes to copy.
 * @return (void *): The original value of [dst].
 */
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*char_dst;
	const unsigned char	*char_src;

	if (len == 0 || dst == src)
		return (dst);
	char_dst = (unsigned char *) dst;
	char_src = (const unsigned char *) src;
	if (dst < src)
	{
		while (len > 0)
		{
			*char_dst++ = *char_src++;
			len--;
		}
	}
	else
	{
		while (len > 0)
		{
			len--;
			*(char_dst + (len)) = *(char_src + (len));
		}
	}
	return (dst);
}
