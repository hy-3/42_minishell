#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_env_param	env_p;
	t_list		*list;
	char		*prompt;
	char		*original_str;

	env_p.first_envp = copy_env(envp);
	env_p.current_envp = copy_env(envp);
	prompt = "minishell> ";
	while (1)
	{
		original_str = readline(prompt);
		//TODO: add history
		list = parse(original_str);
		free(original_str);
		if (list == NULL)
			continue ;
		env_p.pathenv = get_value_of_pathenv(env_p.current_envp);
		env_p.num_of_child = 0;
		env_p.num_of_next_node = count_next_node(list);
		pipex(list, &env_p);
		//TODO: Free env_p(first_envp, current_envp, pathenv)

		/* --- to check args --- */
		t_list *ex;
		int	i = 0;
		int	k;
		printf("//=====\n");
		while (list != NULL)
		{
			printf("node[%i]:%s.", i, list->str);
			printf("\n");
			k = 0;
			ex = list->extra;
			while (ex != NULL)
			{
				printf("node[%i.%i]:%s.",i,k,ex->str);
				printf("\n");
				ex = ex->extra;
				k++;
			}
			list = list->next;
			i++;
		}
		printf("=====//\n");
		/* ---------------- */
	}
	//TODO: clear gnl global var?
}
