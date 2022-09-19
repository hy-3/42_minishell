/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:05:19 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/09/19 17:05:21 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_output_fd(t_cmd *cmd, t_env *env, int i)
{
	if (cmd->output_fd != 1)
		return (cmd->output_fd);
	else if (env->num_of_next_node > (i + 1))
		return (env->p[i][1]);
	else
		return (1);
}
