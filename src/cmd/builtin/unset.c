#include "../../minishell.h"

void	exec_unset(t_cmd *cmd, t_env *env, int i)
{
	if (cmd->num_of_args == 1 || env->num_of_next_node > (i + 1))
		return ;
	else
		env->current_envp = upd_to_new_env(env, cmd);
}
