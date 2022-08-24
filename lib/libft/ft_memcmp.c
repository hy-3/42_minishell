/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:36:54 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/19 11:16:51 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Compare [s1] and [s2]. Both strings are assumed to be [n] bytes.
 *
 * @param s1(const void *): Source string.
 * @param s2(const void *): Source string.
 * @param n(size_t): Assumed bytes size of both strings.
 * @return (int): Retuen 0 if [s1] and [s2] are identical.
 *                Otherwise, return a difference of char([s1] - [s2]).
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*char_s1;
	unsigned char	*char_s2;

	char_s1 = (unsigned char *) s1;
	char_s2 = (unsigned char *) s2;
	while (n > 0)
	{
		if (*char_s1 != *char_s2)
			return (*char_s1 - *char_s2);
		char_s1++;
		char_s2++;
		n--;
	}
	return (0);
}
