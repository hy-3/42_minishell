/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:36:42 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/19 11:14:32 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Find the first occurence of [c] from [s].
 *
 * @param s(const void *): Pointer to source.
 * @param c(int): Char which will be looked for.
 * @param n(size_t): Bytes to look for.
 * @return (void *): Pointer to the byte located or
 *                   NULL if [c] doesn't exist in [n] bytes.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*tmp_s;
	unsigned char	tmp_c;

	tmp_s = (unsigned char *) s;
	tmp_c = c;
	while (n > 0)
	{
		if (*tmp_s == tmp_c)
			return (tmp_s);
		tmp_s++;
		n--;
	}
	return (NULL);
}
