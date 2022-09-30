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
	char	*cmdpath;

	cmdpath = is_cmd_exist_and_executable(env->pathenv, cmd->exec_args[0]);
	if (cmdpath == NULL && ft_strchr(cmd->exec_args[0], '/') != NULL)
		cust_write("No such file or directory\n", 127);
	if (open(cmdpath, O_DIRECTORY) != -1)
		cust_write("is a directory\n", 126);
	if (execve(cmdpath, cmd->exec_args, env->current_envp) == -1)
		cust_write("command not found\n", 127);
}

void	exec_external_cmd(t_cmd *cmd, t_env *env, int i)
{
	g_condition = 2;
	cmd->pid = fork();
	if (cmd->pid < 0)
		cust_perror("Error(fork: cmd->pid)", 1);
	if (cmd->pid == 0)
	{
		organize_fd(cmd, env, i);
		child(cmd, env);
	}
	env->num_of_child += 1;
}
