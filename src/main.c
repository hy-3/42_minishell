/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:04:05 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/09/28 15:23:20 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prep(t_env *env, char **envp)
{
	env->current_envp = copy_env(envp);
	increment_shlvl(env);
	env->status_code = 0;
	change_terminal_setting();
	handle_signals();
	g_condition = 0;
}

void	handle_globalvar_and_status_code(t_env *env)
{
	if (g_condition == -1)
		env->status_code = 1;
	if (g_condition == -2)
		env->status_code = 130;
	g_condition = 0;
}

void	handle_ctrld(void)
{
	printf("exit\n");
	exit(0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_env	env;
	t_list	*list;
	char	*original_str;

	if (argc != 1 || argv[1])
		return (0);
	prep(&env, envp);
	while (1)
	{
		handle_globalvar_and_status_code(&env);
		original_str = readline("minishell> ");
		if (!original_str)
			handle_ctrld();
		if (ft_strncmp(original_str, "", 2) == 0)
			env.status_code = 0;
		save_history(original_str);
		list = parse(original_str, &env);
		free(original_str);
		if (list == NULL)
			continue ;
		pipex(list, &env);
		free_list(list);
	}
	free(env.current_envp);
	return (0);
}
