/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stderr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:06:07 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/09/19 17:06:09 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cust_perror(char *str, int status)
{
	perror(str);
	exit(status);
}

void	cust_write(char *str, int status)
{
	int	n;

	n = ft_strlen(str);
	write(2, str, n);
	exit(status);
}
