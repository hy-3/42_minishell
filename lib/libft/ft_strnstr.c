/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:39:28 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/16 15:16:53 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Find first occurence of [needle] from haystack,
 *        not more than [len] will be searched.
 * @param haystack(const char *): String it will search from.
 * @param needle(const char *): String which will be searched.
 * @param len(size_t): Size of bytes to be searched.
 * @return (char *): If [needle] is empty string -> [haystack]
                     If [needle] isn't found -> NULL
                     Else -> Pointer of first char of first occurence.
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	k;

	i = 0;
	if (haystack == needle)
		return ((char *)haystack);
	if (*needle == '\0')
		if (len == 0 || haystack[i] == '\0')
			return ((char *)&haystack[i]);
	while (haystack[i] != '\0' && i < len)
	{
		k = 0;
		while (haystack[i] == needle[k] && haystack[i] != '\0' && i < len)
		{
			k++;
			i++;
		}
		if (needle[k] == '\0')
			return ((char *)(&haystack[i - k]));
		i -= (k - 1);
	}
	return (NULL);
}
