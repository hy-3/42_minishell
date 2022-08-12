/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:40:08 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/13 17:40:10 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Convert capital case character to lower case.
 * 
 * @param c(int): Given character.
 * @return (int): Lower case character or asis.
 */
int	ft_toupper(int c)
{
	if (96 < c && c < 123)
		return (c - 32);
	else
		return (c);
}
