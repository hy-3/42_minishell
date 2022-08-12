/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:37:15 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/19 11:20:53 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Write [len] bytes of char[c] to string[b].
 *
 * @param b(void *): Target string.
 * @param c(int): Character to be written.
 * @param len(size_t): Bytes to be write.
 * @return (void *): Target string[b].
 */
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*tmp_b;

	tmp_b = (unsigned char *) b;
	while (len > 0)
	{
		*tmp_b++ = (unsigned char) c;
		len--;
	}
	return (b);
}
