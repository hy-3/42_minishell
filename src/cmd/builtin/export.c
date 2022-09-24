/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:02:43 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/09/19 19:11:26 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**handle_export(char **old_envp, char *str, t_env *env)
{
	char	**new_envp;
	char	*pos_equal;

	if (is_valid_envname(str) == 0)
	{
		printf("export: `%s': not a valid identifier\n", str);
		env->status_code = 1;
		return (old_envp);
	}
	if (is_exist_in_env(old_envp, str) == 0)
		return (create_newenv_add(old_envp, str));
	pos_equal = ft_strchr(str, '=');
	new_envp = create_newenv_upd(old_envp, str, pos_equal);
	if (new_envp != NULL)
		return (new_envp);
	return (old_envp);
}

void	print_export(t_env *env, int fd)
{
	int		k;
	char	*new_str;

	k = 0;
	while (env->current_envp[k] != NULL)
	{
		new_str = ft_strjoin("declare -x ", env->current_envp[k]);
		write(fd, new_str, ft_strlen(new_str));
		write(fd, "\n", 1);
		free(new_str);
		k++;
	}
}

void	exec_export(t_cmd *cmd, t_env *env, int i)
{
	int	k;

	if (cmd->num_of_args == 1)
		print_export(env, get_output_fd(cmd, env, i));
	else
	{
		k = 1;
		while (cmd->exec_args[k] != NULL)
		{
			env->current_envp = \
				handle_export(env->current_envp, cmd->exec_args[k++], env);
		}
	}
}
