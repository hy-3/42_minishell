/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:03:20 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/09/19 17:08:54 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child(t_cmd *cmd, t_env *env)
{
	char	*cmdath;

	cmdath = is_cmd_exist_and_executable(env->pathenv, cmd->exec_args[0]);
	if (execve(cmdath, cmd->exec_args, env->current_envp) == -1)
		cust_write("command not found\n", 127);
}

void	exec_external_cmd(t_cmd *cmd, t_env *env, int i)
{
	cmd->pid = fork();
	if (cmd->pid < 0)
		cust_perror("Error(fork: cmd->pid)", 1);
	if (cmd->pid == 0)
	{
		organize_fd(cmd, env, i);
		child(cmd, env);
	}
	if (cmd->is_heredoc == 1)
	{
		if (close(cmd->heredoc_p[0]) == -1)
			cust_perror("Error(close: cmd->heredoc_p[0])", 1);
		if (close(cmd->heredoc_p[1]) == -1)
			cust_perror("Error(close: cmd->heredoc_p[1])", 1);
	}
	if (i > 0)
		if (!((close(env->p[i - 1][0]) == 0) && (close(env->p[i - 1][1]) == 0)))
			cust_perror("Error(close: p[i - 1][0] or p[i - 1][1])", 1);
	env->num_of_child += 1;
}
