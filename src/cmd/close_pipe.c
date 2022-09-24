/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:12:37 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/09/24 18:12:39 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_pipes_when_ctrlc(t_env *env, t_cmd *cmd, int i)
{
	if (g_condition < 0)
	{
		if (close(env->p[i][0]) == -1)
			cust_perror("Error(close: env->p[i][0])", 1);
		if (close(env->p[i][1]) == -1)
			cust_perror("Error(close: env->p[i][1])", 1);
		if (close(cmd->heredoc_p[0]) == -1)
			cust_perror("Error(close: cmd->heredoc_p[0])", 1);
		if (close(cmd->heredoc_p[1]) == -1)
			cust_perror("Error(close: cmd->heredoc_p[1])", 1);
		return ;
	}
}

void	close_pipes(t_env *env, t_cmd *cmd, int i)
{
	if (cmd->is_heredoc == 1)
	{
		if (close(cmd->heredoc_p[0]) == -1)
			cust_perror("Error(close: cmd->heredoc_p[0])", 1);
		if (close(cmd->heredoc_p[1]) == -1)
			cust_perror("Error(close: cmd->heredoc_p[1])", 1);
	}
	if (i > 0)
	{
		if (close(env->p[i - 1][0]) == -1)
			cust_perror("Error(close: env->p[i][0])", 1);
		if (close(env->p[i - 1][1]) == -1)
			cust_perror("Error(close: env->p[i][1])", 1);
	}
	if (cmd->input_fd != 0)
		if (close(cmd->input_fd) == -1)
			cust_perror("Error(close: input_fd", 1);
	if (cmd->output_fd != 1)
		if (close(cmd->output_fd) == -1)
			cust_perror("Error(close: output_fd", 1);
}
