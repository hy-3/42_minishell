#include "../minishell.h"

int	get_output_fd(t_cmd_param *cmd_p, t_env_param *env_p, int i)
{
	if (cmd_p->output_fd != 1)
		return (cmd_p->output_fd);
	else if (env_p->num_of_next_node > (i + 1))
		return (cmd_p->p[i][1]);
	else
		return (1);
}