/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:38:03 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/16 20:20:26 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_positive_int_digits(int n)
{
	int	count;

	count = 1;
	while (n > 9)
	{
		count++;
		n /= 10;
	}
	return (count);
}

void	print_int_lowest_num(int fd)
{
	char	*num;
	int		i;

	write(fd, "-", 1);
	num = "2147483648";
	i = 0;
	while (i < 10)
		write(fd, &num[i++], 1);
}

int	base_ten_power(int n)
{
	int	res;

	res = 1;
	while (n-- > 0)
		res *= 10;
	return (res);
}

/**
 * @brief Output given integer[i] to given file discriptor[fd].
 * 
 * @param n(int): Integer to output.
 * @param fd(int): File discriptor.
 * @return (void)
 */
void	ft_putnbr_fd(int n, int fd)
{
	int		digit;
	char	each_int;

	if (n == -2147483648)
		print_int_lowest_num(fd);
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n *= -1;
		}
		digit = count_positive_int_digits(n);
		while (digit > 0)
		{
			each_int = n / base_ten_power(digit - 1) + '0';
			write(fd, &each_int, 1);
			n %= base_ten_power(digit - 1);
			digit--;
		}
	}
}
