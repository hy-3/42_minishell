/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:38:57 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/15 15:31:25 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copy strings(from [src] to [dst]) up to [dstsize] - 1 characters.
 *
 * @param dst(char *): Pointer to destination string.
 * @param src(char *): Pointer to source string.
 * @param dstsize(size_t): Size of destination.
 * @return (size_t): Length of [src].
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len_src;
	size_t	i;

	len_src = ft_strlen(src);
	if (dstsize == 0)
		return (len_src);
	i = 0;
	while (src[i] != '\0' && dstsize > 0)
	{
		dst[i] = src[i];
		i++;
		dstsize--;
	}
	if (dstsize == 0)
		i -= 1;
	dst[i] = '\0';
	return (len_src);
}
