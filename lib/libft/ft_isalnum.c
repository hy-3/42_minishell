/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:35:28 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/13 17:35:29 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Check if given char[i] is alphabet or number.
 * 
 * @param i(int): Character which will be checked.
 * @return (int): If it is true, return 1. If not, return 0.
 */
int	ft_isalnum(int i)
{
	if ((64 < i && i < 91) || (96 < i && i < 123) || (47 < i && i < 58))
		return (1);
	else
		return (0);
}
