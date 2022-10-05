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

int	write_heredoc(t_list *list, t_cmd *cmd, char *str)
{
	char	*str_with_newline;

	if (g_condition == -1)
	{
		cmd->is_error = 1;
		free(str);
		return (1);
	}
	if (str == NULL \
			|| ft_strncmp(str, list->str, ft_strlen(list->str) + 1) == 0)
	{
		free(str);
		return (1);
	}
	str_with_newline = ft_strjoin(str, "\n");
	write(cmd->heredoc_p[1], str_with_newline, ft_strlen(str_with_newline));
	free(str);
	free(str_with_newline);
	return (0);
}

void	handle_err2(char *str, t_env *env, t_cmd *cmd, int status_code)
{
	printf("%s\n", str);
	env->status_code = status_code;
	cmd->is_error = 2;
	cmd->input_fd = 0;
}

void	handle_err1(char *str, t_env *env, t_cmd *cmd, int status_code)
{
	printf("%s\n", str);
	env->status_code = status_code;
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
	int	fd;

	list = list->extra;
	if (list == NULL)
		handle_err1("syntax error near unexpected token", env, cmd, 258);
	else
	{
		fd = open(list->str, O_CREAT | O_TRUNC | O_WRONLY, 0777);
		if (fd == -1)
			cust_write("file open error with <>\n", 1);
		list = list->extra;
		if (close(fd) == -1)
			cust_perror("Error(close: fd with <>)", 1);
	}
	return (list);
}
