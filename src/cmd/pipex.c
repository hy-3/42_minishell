#include "../minishell.h"

void	cust_waitpid(int num_of_executed_cmd)
{
	while (num_of_executed_cmd-- > 0)
	{
		if (waitpid(-1, NULL, 0) == -1)
			cust_perror("Error(cust_waitpid)", 1);
	}
}

int	exec_cmd(t_list *list, t_env_param *env_p, int i, int num_node_hor)
{
	t_cmd_param	cmd_p;
	int			k;
	int			num_node_ver;

	k = 0;
	cmd_p.exec_args[k++] = list->str;
	num_node_ver = count_extra_node(list);
	list = list->extra;
	while (list != NULL)
	{
		cmd_p.exec_args[k++] = list->str;
		list = list->extra;
	}
	cmd_p.exec_args[num_node_ver] = NULL;
	return (exec_basedon_cmdtype(&cmd_p, env_p, num_node_ver, num_node_hor, i));
}

int	pipex(t_list *list, t_env_param *env_p)
{
	int			status_code; //TODO: get from last exec cmd.
	char		*pathenv;
	int			num_node_hor;
	int			num_of_child;

	status_code = 0;
	num_node_hor = count_next_node(list);
	num_of_child = list_iter(list, env_p, num_node_hor, exec_cmd);
	cust_waitpid(num_of_child);
	return (status_code);
}
