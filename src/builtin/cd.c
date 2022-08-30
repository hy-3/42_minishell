
#include "../minishell.h"
//TODO: check every builtins to work with output fd
//TODO: change to work together with pipe (with external executable)

void	exec_cd(t_cmd_param *cmd_p, int num_node_ver)
{
	if (num_node_ver == 2)
		chdir(cmd_p->exec_args[1]); //TODO: throw error if directory is not found.
	else
		cust_write("ERROR: Specify relative or absolute path\n", 1); //TODO: error handle
}
