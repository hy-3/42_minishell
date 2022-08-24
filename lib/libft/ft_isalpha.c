/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:11:37 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/13 16:52:04 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Check if given char[i] is alphabet.
 * 
 * @param i(int): Character which will be checked.
 * @return (int): If it is true, return 1. If not, return 0.
 */
int	ft_isalpha(int i)
{
	if ((64 < i && i < 91) || (96 < i && i < 123))
		return (1);
	else
		return (0);
}
