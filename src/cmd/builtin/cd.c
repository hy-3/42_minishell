/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:02:08 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/09/28 19:29:02 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	upd_pwd(t_env *env, char *old_path)
{
	char	path[PATH_MAX];
	char	*new_pwd_full;
	char	*old_pwd_full;

	getcwd(path, PATH_MAX);
	new_pwd_full = ft_strjoin("PWD=", path);
	old_pwd_full = ft_strjoin("OLDPWD=", old_path);
	env->current_envp = handle_export(env->current_envp, new_pwd_full, env);
	env->current_envp = handle_export(env->current_envp, old_pwd_full, env);
	free(new_pwd_full);
	free(old_pwd_full);
}

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
	char	old_path[PATH_MAX];

	getcwd(old_path, PATH_MAX);
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
		upd_pwd(env, old_path);
	}
}
