#include "../../minishell.h"

void	exec_cd(t_cmd_param *cmd_p, t_env_param *env_p, int i)
{
	char	*var;

	if (env_p->num_of_next_node == (i + 1))
	{
		if (cmd_p->num_of_args == 1)
		{
			var = getenv("HOME");
			if (chdir(var) == -1)
				printf("%s: No such file or directory\n", cmd_p->exec_args[1]);
		}
		else
		{
			if (chdir(cmd_p->exec_args[1]) == -1)
				printf("%s: No such file or directory\n", cmd_p->exec_args[1]);
		}
	}
}
