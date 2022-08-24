/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:38:51 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/16 19:42:41 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Concatenate string from [src] to [dst]
 *        up to [dstsize] - strlen(dst) - 1.
 * 
 * @param dst(char *): Pointer to destination string.
 * @param src(const char *): Pointer to source string.
 * @param dstsize(size_t): Size to concatenate.
 * @return (size_t):
 *    If (length of [dst] < [dstsize]) -> length of [src] + length of [dst]
 *    Else -> length of [src] + [dstsize].
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	res;
	size_t	i;
	size_t	k;

	res = ft_strlen(src);
	i = ft_strlen(dst);
	if (i < dstsize)
	{
		res += ft_strlen(dst);
		k = 0;
		while (src[k] != '\0' && (dstsize - i) > 0)
			dst[i++] = src[k++];
	}
	else
		return (res + dstsize);
	if ((dstsize - i) == 0)
		i -= 1;
	dst[i] = '\0';
	return (res);
}
