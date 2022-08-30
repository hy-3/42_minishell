#include "../minishell.h"

//TODO: check every builtins to work with output fd
//TODO: change to work together with pipe (with external executable)

void	exec_env(t_cmd_param *cmd_p, t_env_param *env_p, int num_node_ver)
{
	int	i;

	if (num_node_ver == 1)
	{
		i = 0;
		while (env_p->current_envp[i] != NULL)
		{
			if (is_exist_in_env(env_p->first_envp, env_p->current_envp[i]) == 1)
				printf("%s\n", env_p->current_envp[i]);
			i++;
		}
	}
	else
		printf("tmp\n"); //TODO: check what should I implement when 'env' has args.
}
