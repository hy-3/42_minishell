/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:46:33 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/06/07 12:32:18 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	wexitstatus(int status)
{
	return (((status) & 0xff00) >> 8);
}
