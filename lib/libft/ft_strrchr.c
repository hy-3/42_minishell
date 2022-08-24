/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:39:43 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/15 21:26:30 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Find the last occurrence of [c] from [s].
 *        \0 is considered as part of source.
 *
 * @param s(const char *): Pointer to source.
 * @param c(int): Char which will be looked for.
 * @return (char *): Pointer of last occurence of [c].
 */
char	*ft_strrchr(const char *s, int c)
{
	size_t	len_s;

	len_s = ft_strlen(s);
	while (len_s > 0)
	{
		if (*(s + len_s) == (char) c)
			return ((char *)(s + len_s));
		len_s--;
	}
	if (*(s + len_s) == (char) c)
		return ((char *)(s + len_s));
	return (NULL);
}
