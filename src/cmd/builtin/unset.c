/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:03:04 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/09/19 17:33:29 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**create_newenv_unset(char **old_envp, char *str)
{
	char	**new_envp;
	int		k;
	int		l;

	new_envp = (char **) malloc(calc_envp_size(old_envp) * sizeof(char *));
	k = 0;
	l = 0;
	while (old_envp[k] != NULL)
	{
		if (count_till_equal(old_envp[k]) == count_till_equal(str))
		{
			if (ft_strncmp(old_envp[k], str, count_till_equal(str)) == 0)
			{
				free(old_envp[k++]);
				continue ;
			}
		}
		new_envp[l++] = ft_strdup(old_envp[k]);
		free(old_envp[k++]);
	}
	free(old_envp);
	new_envp[l] = NULL;
	return (new_envp);
}

char	**handle_unset(t_env *env, t_cmd *cmd)
{
	char	**new_envp;
	int		i;

	i = 1;
	while (cmd->exec_args[i] != NULL)
	{
		if (i == 1)
			new_envp = \
				create_newenv_unset(env->current_envp, cmd->exec_args[i]);
		else
			new_envp = create_newenv_unset(new_envp, cmd->exec_args[i]);
		i++;
	}
	return (new_envp);
}

void	exec_unset(t_cmd *cmd, t_env *env, int i)
{
	if (cmd->num_of_args == 1 || env->num_of_next_node > (i + 1))
		return ;
	else
		env->current_envp = handle_unset(env, cmd);
}
