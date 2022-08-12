/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:36:13 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/13 17:36:16 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Check if given char[i] is number.
 * 
 * @param i(int): Character which will be checked.
 * @return (int): If it is true, return 1. If not, return 0.
 */
int	ft_isdigit(int i)
{
	if (47 < i && i < 58)
		return (1);
	else
		return (0);
}
