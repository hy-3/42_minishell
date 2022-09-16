#include "../../minishell.h"

void	exec_cd(t_cmd *cmd, t_env *env, int i)
{
	char	*var;

	if (env->num_of_next_node == (i + 1))
	{
		if (cmd->num_of_args == 1)
		{
			var = getenv("HOME");
			if (chdir(var) == -1)
			{
				printf("%s: No such file or directory\n", cmd->exec_args[1]);
				env->status_code = 1;
			}
		}
		else
		{
			if (chdir(cmd->exec_args[1]) == -1)
			{
				printf("%s: No such file or directory\n", cmd->exec_args[1]);
				env->status_code = 1;
			}
		}
	}
}
