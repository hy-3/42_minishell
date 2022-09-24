/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:02:16 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/09/19 19:11:18 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cmd_env(t_env *env, int fd)
{
	int	k;

	k = 0;
	while (env->current_envp[k] != NULL)
	{
		if (ft_strchr(env->current_envp[k], '=') != NULL)
		{
			write(fd, env->current_envp[k], ft_strlen(env->current_envp[k]));
			write(fd, "\n", 1);
		}
		k++;
	}
}

void	exec_env(t_cmd *cmd, t_env *env, int i)
{
	if (cmd->num_of_args == 1)
		cmd_env(env, get_output_fd(cmd, env, i));
	else
	{
		printf("env: %s: No such file or directory\n", cmd->exec_args[1]);
		env->status_code = 127;
	}
}
