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

void	convert_dollar_part(t_fill *fill, t_env *env, t_dollar *dollar)
{
	int		i;
	char	*var;

	dollar->is_free_needed = 0;
	upd_dollar_start_and_end(fill, dollar);
	var = (char *) malloc((dollar->end - dollar->start + 1) * sizeof(char));
	if (var == NULL)
		cust_write("malloc failed\n", 1);
	i = 0;
	while (++(dollar->start) < dollar->end)
		var[i++] = fill->tmp_str[dollar->start];
	var[i] = '\0';
	if (var[0] == '?')
	{
		dollar->str_dollar_part = ft_itoa(env->status_code);
		dollar->end = find_question_position(fill->tmp_str) + 1;
		dollar->is_free_needed = 1;
	}
	else
		dollar->str_dollar_part = getenv(var);
	if (dollar->str_dollar_part == NULL)
		dollar->size_dollar_part = 0;
	else
		dollar->size_dollar_part = ft_strlen(dollar->str_dollar_part);
	free(var);
}

char	*convert_str_from_dollar(t_fill *fill, t_env *env)
{
	t_dollar	dollar;
	int			i;
	int			k;
	char		*converted_str;

	if (g_condition == -1)
		env->status_code = 1;
	convert_dollar_part(fill, env, &dollar);
	converted_str = (char *) malloc(calc_length(&dollar, fill) * sizeof(char));
	if (converted_str == NULL)
		cust_write("malloc failed\n", 1);
	i = -1;
	while (++i < dollar.tmp_start)
		converted_str[i] = fill->tmp_str[i];
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
