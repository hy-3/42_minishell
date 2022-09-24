/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:11:27 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/09/24 18:11:29 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	calc_length(t_dollar *dollar, t_fill *fill)
{
	int	total_length;

	total_length = dollar->tmp_start + dollar->size_dollar_part + \
					(ft_strlen(fill->tmp_str) - dollar->end) + 1;
	return (total_length);
}

int	find_question_position(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '?')
			break ;
		i++;
	}
	return (i);
}

int	is_dollar_exist(char *tmp_str)
{
	int	i;

	i = 0;
	while (tmp_str[i] != '\0')
	{
		if (tmp_str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	upd_dollar_start_and_end(t_fill *fill, t_dollar *dollar)
{
	int	i;

	i = 0;
	while (fill->tmp_str[i] != '$')
		i++;
	dollar->start = i;
	dollar->tmp_start = dollar->start;
	if (fill->end_pos_of_dollar_var > 0)
		while (fill->tmp_str[i] != '\0' && fill->tmp_str[i] != 39 && \
				fill->tmp_str[i] != 34 && fill->tmp_str[i] != ' ' && \
				i < fill->end_pos_of_dollar_var)
			i++;
	else
		while (fill->tmp_str[i] != '\0' && fill->tmp_str[i] != 39 && \
				fill->tmp_str[i] != 34 && fill->tmp_str[i] != ' ')
			i++;
	dollar->end = i;
}
