#include "../../minishell.h"

//TODO: check every builtins to work with output fd
//TODO: change to work together with pipe (with external executable)

void	exec_export(t_cmd_param *cmd_p, t_env_param *env_p)
{
	int	k;

	k = 0;
	if (cmd_p->num_of_args == 1)
		while (env_p->current_envp[k] != NULL)
			printf("declare -x %s\n", env_p->current_envp[k++]); //TODO: check if I need to add "" for values.
	else
	{
		k = 1;
		while (cmd_p->exec_args[k] != NULL)
			env_p->current_envp = create_new_env_with_str(env_p->current_envp, cmd_p->exec_args[k++]);
	}
}