/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arrows.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:05:28 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/09/19 18:10:57 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*single_right_arrow(t_list *list, t_cmd *cmd, t_env *env)
{
	list = list->extra;
	if (list == NULL)
		handle_err1("syntax error near unexpected token", env, cmd, 258);
	else
	{
		if (is_special_char(list->str[0]) == 1)
			handle_err1("syntax error near unexpected token", env, cmd, 258);
		else
		{
			cmd->output_fd = \
				open(list->str, O_CREAT | O_TRUNC | O_WRONLY, 0777);
			if (cmd->output_fd == -1)
				handle_err1("Permission denied", env, cmd, 1);
		}
		list = list->extra;
	}
	return (list);
}

t_list	*double_right_arrow(t_list *list, t_cmd *cmd, t_env *env)
{
	list = list->extra;
	if (list == NULL)
		handle_err1("syntax error near unexpected token", env, cmd, 258);
	else
	{
		if (is_special_char(list->str[0]) == 1)
			handle_err1("syntax error near unexpected token", env, cmd, 258);
		else
		{
			cmd->output_fd = \
				open(list->str, O_CREAT | O_APPEND | O_WRONLY, 0777);
			if (cmd->output_fd == -1)
				handle_err1("Permission denied", env, cmd, 1);
		}
		list = list->extra;
	}
	return (list);
}

t_list	*single_left_arrow(t_list *list, t_cmd *cmd, t_env *env)
{
	list = list->extra;
	if (list == NULL)
		handle_err1("syntax error near unexpected token", env, cmd, 258);
	else
	{
		if (is_special_char(list->str[0]) == 1)
			handle_err1("syntax error near unexpected token", env, cmd, 258);
		else
		{
			cmd->input_fd = open(list->str, O_RDONLY);
			if (access(list->str, F_OK) == -1)
				handle_err2("No such file or directory", env, cmd, 1);
			else if (cmd->input_fd == -1)
				handle_err2("Permission denied", env, cmd, 1);
		}
		list = list->extra;
	}
	return (list);
}

t_list	*double_left_arrow(t_list *list, t_cmd *cmd, t_env *env)
{
	char	*str;
	char	*limit_str;

	list = list->extra;
	if (list == NULL)
		handle_err1("syntax error near unexpected token", env, cmd, 258);
	else
	{
		if (is_special_char(list->str[0]) == 1)
			handle_err1("syntax error near unexpected token", env, cmd, 258);
		else
		{
			if (pipe(cmd->heredoc_p) < 0)
				cust_perror("Error(pipe: heredoc_p)", 1);
			limit_str = ft_strjoin(list->str, "\n");
			while (1)
			{
				str = get_next_line(0);
				if (ft_strncmp(str, limit_str, ft_strlen(limit_str)) == 0)
				{
					free(str);
					break ;
				}
				write(cmd->heredoc_p[1], str, ft_strlen(str));
				free(str);
			}
			free(limit_str);
			cmd->is_heredoc = 1;
		}
		list = list->extra;
	}
	return (list);
}

t_list	*check_arrows(t_list *list, t_cmd *cmd, t_env *env)
{
	if (ft_strncmp(list->str, ">", 2) == 0)
		list = single_right_arrow(list, cmd, env);
	else if (ft_strncmp(list->str, ">>", 3) == 0)
		list = double_right_arrow(list, cmd, env);
	else if (ft_strncmp(list->str, "<", 2) == 0)
		list = single_left_arrow(list, cmd, env);
	else if (ft_strncmp(list->str, "<<", 3) == 0)
		list = double_left_arrow(list, cmd, env);
	else if (ft_strncmp(list->str, "<>", 3) == 0)
		list = arrow_special_case(list, cmd, env);
	else
	{
		if (ft_strchr(list->str, '<') != NULL \
				|| ft_strchr(list->str, '>') != NULL)
		{
			handle_err1("syntax error near unexpected token", env, cmd, 258);
			list = NULL;
		}
	}
	return (list);
}
