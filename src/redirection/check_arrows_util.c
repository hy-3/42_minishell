/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arrows_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:07:36 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/09/19 19:12:28 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_err2(char *str, t_env *env, t_cmd *cmd, int status_code)
{
	printf("%s\n", str);
	g_status_code = status_code;
	cmd->is_error = 2;
}

void	handle_err1(char *str, t_env *env, t_cmd *cmd, int status_code)
{
	printf("%s\n", str);
	g_status_code = status_code;
	cmd->is_error = 1;
}

int	is_special_char(char first_char)
{
	if (first_char == '>' || first_char == '<' || first_char == '|')
		return (1);
	return (0);
}

t_list	*arrow_special_case(t_list *list, t_cmd *cmd, t_env *env)
{
	list = list->extra;
	if (list == NULL)
		handle_err1("syntax error near unexpected token", env, cmd, 258);
	else
	{
		open(list->str, O_CREAT | O_TRUNC | O_WRONLY, 0777);
		list = list->extra;
	}
	return (list);
}
