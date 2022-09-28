/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:02:08 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/09/28 18:59:17 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cd_to_home(t_cmd *cmd, t_env *env)
{
	char	*var;

	var = getenv("HOME");
	if (chdir(var) == -1)
	{
		printf("%s: No such file or directory\n", cmd->exec_args[1]);
		env->status_code = 1;
	}
}

void	cd_to_oldpwd(t_cmd *cmd, t_env *env)
{
	char	*var;

	var = cust_getenv("OLDPWD", env);
	if (chdir(var) == -1)
	{
		printf("%s: No such file or directory\n", cmd->exec_args[1]);
		env->status_code = 1;
	}
}

void	exec_cd(t_cmd *cmd, t_env *env, int i)
{
	if (env->num_of_next_node == (i + 1))
	{
		if (cmd->num_of_args == 1)
			cd_to_home(cmd, env);
		else
		{
			if (ft_strncmp(cmd->exec_args[1], "~", 2) == 0)
				cd_to_home(cmd, env);
			else if (ft_strncmp(cmd->exec_args[1], "-", 2) == 0)
				cd_to_oldpwd(cmd, env);
			else
			{
				if (chdir(cmd->exec_args[1]) == -1)
				{
					printf("%s: No such file or directory\n", cmd->exec_args[1]);
					env->status_code = 1;
				}
			}
		}
	}
}
