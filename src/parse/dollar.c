/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:04:54 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/09/19 19:11:53 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	convert_dollar_part(t_fill *fill, t_env *env, t_dollar *dollar)
{
	int		i;
	char	*var_name;

	dollar->is_free_needed = 0;
	upd_dollar_start_and_end(fill, dollar);
	var_name = (char *) malloc((dollar->end - dollar->start + 1) \
					* sizeof(char));
	if (var_name == NULL)
		cust_write("malloc failed\n", 1);
	i = 0;
	dollar->start++;
	while (dollar->start < dollar->end)
		var_name[i++] = fill->tmp_str[dollar->start++];
	var_name[i] = '\0';
	if (var_name[0] == '?')
	{
		dollar->str_dollar_part = ft_itoa(env->status_code);
		dollar->end = find_question_position(fill->tmp_str) + 1;
		dollar->is_free_needed = 1;
	}
	else
		dollar->str_dollar_part = getenv(var_name);
	if (dollar->str_dollar_part == NULL)
		dollar->size_dollar_part = 0;
	else
		dollar->size_dollar_part = ft_strlen(dollar->str_dollar_part);
	free(var_name);
}

char	*convert_str_from_dollar(t_fill *fill, t_env *env)
{
	t_dollar	dollar;
	int			i;
	int			k;
	int			total_length;
	char		*converted_str;

	if (g_condition == -1)
		env->status_code = 1;
	convert_dollar_part(fill, env, &dollar);
	total_length = dollar.tmp_start + dollar.size_dollar_part + \
					(ft_strlen(fill->tmp_str) - dollar.end) + 1;
	converted_str = (char *) malloc(total_length * sizeof(char));
	if (converted_str == NULL)
		cust_write("malloc failed\n", 1);
	i = 0;
	while (i < dollar.tmp_start)
	{
		converted_str[i] = fill->tmp_str[i];
		i++;
	}
	k = 0;
	while (k < dollar.size_dollar_part)
		converted_str[i++] = dollar.str_dollar_part[k++];
	while (fill->tmp_str[dollar.end] != '\0')
		converted_str[i++] = fill->tmp_str[dollar.end++];
	converted_str[i] = '\0';
	if (dollar.is_free_needed == 1)
		free(dollar.str_dollar_part);
	g_condition = 0;
	return (converted_str);
}
