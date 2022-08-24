/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:37:50 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/13 17:37:51 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Outpu character to given file discriptor[fd].
 * 
 * @param c(char): Character to output.
 * @param fd(int): File discriptor.
 * @return (void)
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
