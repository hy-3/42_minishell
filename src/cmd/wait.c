/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:12:02 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/09/24 18:12:04 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	wexitstatus(int status)
{
	return (((status) & 0xff00) >> 8);
}

void	cust_waitpid(int num_of_executed_cmd)
{
	if (g_condition == -1)
		return ;
	while (num_of_executed_cmd-- > 0)
	{
		if (waitpid(-1, NULL, 0) == -1)
			cust_perror("Error(cust_waitpid)", 1);
	}
}

void	handle_wait(t_env *env, t_cmd *cmd)
{
	if (cmd->pid != 0)
	{
		env->num_of_child--;
		waitpid(cmd->pid, &(env->status_code), 0);
		env->status_code = wexitstatus(env->status_code);
	}
	cust_waitpid(env->num_of_child);
}
