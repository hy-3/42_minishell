/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:04:46 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/09/19 17:04:48 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_include_cmd(char *original_str, t_fill *fill)
{
	while (original_str[fill->start] == ' ')
		fill->start++;
	if (original_str[fill->start] == '|' || original_str[fill->start] == '\0')
		return (0);
	return (1);
}

void	check_quote_condition(t_parse *parse, char c)
{
	if (c == 39)
		parse->num_of_single_quote++;
	if (c == 34)
		parse->num_of_double_quote++;
	if (parse->num_of_single_quote % 2 == 0 && parse->num_of_double_quote % 2 == 0)
		parse->is_quote_closed = 1;
	else
		parse->is_quote_closed = 0;
}

int	check_pipe_num(char *original_str, int k)
{
	int	num_of_pipe;

	num_of_pipe = 1;
	while (original_str[k] != '\0' && original_str[k] != ' ')
	{
		if (original_str[k] == '|')
			num_of_pipe++;
		k++;
	}
	return (num_of_pipe);
}

void	check_pipe_condition(char *original_str, t_parse *parse, t_env *env)
{
	int	num_of_pipe;

	num_of_pipe = 0;
	if (parse->i == 0)
	{
		printf("parse error near `|'\n");
		free(parse->first_node);
		env->status_code = 258;
		parse->first_node = NULL;
		parse->pipe_condition = 2;
		return ;
	}
	num_of_pipe = check_pipe_num(original_str, parse->i + 1);
	if (num_of_pipe > 2)
	{
		printf("syntax error near unexpected token `|' (pipe continued)\n");
		free(parse->first_node);
		env->status_code = 258;
		parse->first_node = NULL;
		parse->pipe_condition = 2;
	}
	if (num_of_pipe == 2)
		parse->pipe_condition = 1;
	return ;
}
