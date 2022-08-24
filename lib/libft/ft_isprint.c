/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:36:25 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/15 12:09:10 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Check if given char[i] is printable (space char inclusive)
 * 
 * @param i(int): Character which will be checked.
 * @return (int): If it is true, return 1. If not, return 0.
 */
int	ft_isprint(int i)
{
	if (31 < i && i < 127)
		return (1);
	else
		return (0);
}
