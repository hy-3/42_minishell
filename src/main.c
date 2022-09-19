/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:04:05 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/09/19 17:04:07 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* -- to check -- */
void leaks()
{
	system("leaks minishell");
}
/* -------------- */

int	main(int argc, char *argv[], char *envp[])
{
	t_env	env;
	t_list	*list;
	char	*original_str;

	if (argc != 1)
		return (0);
	// atexit(leaks); //TODO: check memory leaks
	env.first_envp = copy_env(envp);
	env.current_envp = copy_env(envp);
	env.status_code = 0;
	change_terminal_setting();
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	while (1)
	{
		original_str = readline("minishell> ");
		if (original_str == 0)
		{
			printf("exit\n");
			exit(0);
		}
		save_history(original_str);
		list = parse(original_str, &env);
		free(original_str);
		if (list == NULL)
			continue ;
		env.pathenv = get_value_of_pathenv(env.current_envp);
		env.num_of_child = 0;
		env.num_of_next_node = count_next_node(list);
		pipex(list, &env);
		free_list(list);
	}
	free(env.first_envp);
	free(env.current_envp);
	return (0);
}

		/* --- to check args --- */
		// t_list *ex;
		// int	i = 0;
		// int	k;
		// printf("//=====\n");
		// while (list != NULL)
		// {
		// 	printf("node[%i]:%s.", i, list->str);
		// 	printf("\n");
		// 	k = 0;
		// 	ex = list->extra;
		// 	while (ex != NULL)
		// 	{
		// 		printf("node[%i.%i]:%s.",i,k,ex->str);
		// 		printf("\n");
		// 		ex = ex->extra;
		// 		k++;
		// 	}
		// 	list = list->next;
		// 	i++;
		// }
		// printf("=====//\n");
		/* ---------------- */
