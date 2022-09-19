/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_upd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:03:43 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/09/19 17:03:44 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**copy_env(char **old_envp)
{
	int		i;
	char	**new_envp;

	i = 0;
	new_envp = (char **) malloc(calc_envp_size(old_envp) * sizeof(char *));
	while (old_envp[i] != NULL)
	{
		new_envp[i] = ft_strdup(old_envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}
