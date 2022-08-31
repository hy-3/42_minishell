#include "../../minishell.h"

void	exec_unset(t_cmd_param *cmd_p, t_env_param *env_p, int i)
{
	if (cmd_p->num_of_args == 1 || env_p->num_of_next_node > (i + 1))
		return ;
	else
		env_p->current_envp = upd_to_new_env(env_p, cmd_p);
}
