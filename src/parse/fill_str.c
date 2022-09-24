/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:05:00 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/09/19 17:49:23 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_arrow_str(char *original_str, t_fill *fill, int i)
{
	int	k;

	fill->tmp_str = (char *) malloc((i + 1) * sizeof(char));
	if (fill->tmp_str == NULL)
		cust_write("malloc failed\n", 1);
	k = 0;
	while (i-- > 0)
		fill->tmp_str[k++] = original_str[fill->start++];
	fill->tmp_str[k] = '\0';
}

void	fill_al(char *original_str, t_fill *fill)
{
	int	i;
	int	start;

	i = 0;
	start = fill->start;
	if (fill->count != 0)
		fill->list = create_extra_node(fill->list);
	while (original_str[start] == '>' || original_str[start] == '<')
	{
		start++;
		i++;
	}
	create_arrow_str(original_str, fill, i);
	fill->list->str = ft_strdup(fill->tmp_str);
}

int	fill_till_quote(char *original_str, t_fill *fill, t_parse *parse, int k)
{
	char	tmp_quote;

	tmp_quote = original_str[fill->start];
	if (fill->current_quote == 0)
		fill->current_quote = tmp_quote;
	else
		if (fill->current_quote == original_str[fill->start])
			fill->current_quote = 0;
	fill->start++;
	while (original_str[fill->start] != tmp_quote)
	{
		if (original_str[fill->start] == '\0')
		{
			printf("quote is not closed.\n");
			free_list(parse->first_node);
			parse->first_node = NULL;
			return (-1);
		}
		fill->tmp_str[k++] = original_str[fill->start++];
	}
	fill->end_pos_of_dollar_var = k;
	fill->start++;
	return (k);
}

void	lastnode_fill_str(t_fill *fill, t_env *env)
{
	if (fill->count != 0)
		fill->list = create_extra_node(fill->list);
	if (is_dollar_exist(fill->tmp_str) == 1 \
			&& (fill->current_quote == 0 || fill->current_quote == 34))
		fill->list->str = convert_str_from_dollar(fill, env);
	else
		fill->list->str = ft_strdup(fill->tmp_str);
}

void	fill_str(char *original_str, t_fill *fill, t_parse *parse, t_env *env)
{
	int	k;

	fill->tmp_str = (char *) malloc((fill->i - fill->start + 1) * sizeof(char));
	if (fill->tmp_str == NULL)
		cust_write("malloc failed\n", 1);
	k = 0;
	while (is_specialchar(original_str[fill->start]) == 0)
	{
		if (original_str[fill->start] == '|')
			break ;
		if (original_str[fill->start] == 34 || original_str[fill->start] == 39)
		{
			k = fill_till_quote(original_str, fill, parse, k);
			if (k == -1)
				return ;
			continue ;
		}
		fill->tmp_str[k++] = original_str[fill->start++];
	}
	fill->tmp_str[k] = '\0';
	lastnode_fill_str(fill, env);
}
