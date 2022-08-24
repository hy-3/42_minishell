/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:37:57 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/15 20:11:45 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Output string[s] to given file discriptor[fd], followed by new line.
 * 
 * @param s(char *): String to output.
 * @param fd(int): File discriptor.
 * @return (void)
 */
void	ft_putendl_fd(char *s, int fd)
{
	int	count;

	count = 0;
	if (s == NULL)
		return ;
	while (s[count] != '\0')
		count++;
	write(fd, s, count);
	write(fd, "\n", 1);
}
