/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:36:33 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/16 20:17:54 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_digits(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		count = 1;
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

/**
 * @brief Convert integer to string.
 * 
 * @param n(int): Source integer.
 * @return (char *): Converted string.
 */
char	*ft_itoa(int n)
{
	int		digit;
	char	*res;

	digit = count_digits(n);
	if (n < 0)
		digit++;
	res = (char *) malloc((digit + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	res[digit--] = '\0';
	if (n < 0)
		res[0] = '-';
	if (n == 0)
		res[0] = '0';
	while (n != 0)
	{
		if (n < 0)
			res[digit--] = n % 10 * -1 + '0';
		else
			res[digit--] = n % 10 + '0';
		n /= 10;
	}
	return (res);
}
