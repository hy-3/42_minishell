#include "../../minishell.h"
//TODO: check every builtins to work with output fd
//TODO: change to work together with pipe (with external executable)

void	exec_unset(t_cmd_param *cmd_p, t_env_param *env_p)
{
	if (cmd_p->num_of_args == 1)
		return ;
	else
		env_p->current_envp = upd_to_new_env(env_p, cmd_p);
}
