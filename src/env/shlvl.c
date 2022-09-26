/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                             :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 20:23:05 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/09/26 20:23:07 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_shlvl(char **current_envp)
{
	int	i;
	int	k;
	int	shlvl;

	i = 0;
	k = 0;
	shlvl = 0;
	while (current_envp[i] != NULL)
	{
		if (ft_strncmp(current_envp[i], "SHLVL=", 6) == 0)
		{
			while (current_envp[i][k] != '=')
				k++;
			shlvl = ft_atoi(&current_envp[i][++k]);
			break ;
		}
		i++;
	}
	return (shlvl);
}

void	increment_shlvl(t_env *env)
{
	int		shlvl;
	char	*str_shlvl;
	char	*str_shlvl_full;

	shlvl = get_shlvl(env->current_envp);
	str_shlvl = ft_itoa(++shlvl);
	str_shlvl_full = ft_strjoin("SHLVL=", str_shlvl);
	free(str_shlvl);
	env->current_envp = handle_export(env->current_envp, str_shlvl_full, env);
	free(str_shlvl_full);
}
