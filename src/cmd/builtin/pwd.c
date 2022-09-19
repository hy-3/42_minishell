/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:02:58 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/09/19 17:03:00 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_pwd(t_cmd *cmd, t_env *env, int i)
{
	char	path[PATH_MAX];
	char	*new_path;

	getcwd(path, PATH_MAX);
	new_path = ft_strjoin(path, "\n");
	write(get_output_fd(cmd, env, i), new_path, ft_strlen(new_path));
	free(new_path);
}
