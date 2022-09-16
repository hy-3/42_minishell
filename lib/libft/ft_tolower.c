/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:40:03 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/13 17:40:04 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Convert lower case character to capital case.
 * 
 * @param c(int): Given character.
 * @return (int): Capital case character or asis.
 */
int	ft_tolower(int c)
{
	if (64 < c && c < 91)
		return (c + 32);
	else
		return (c);
}
