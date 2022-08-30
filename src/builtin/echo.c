#include "../minishell.h"

//TODO: check every builtins to work with output fd
//TODO: change to work together with pipe (with external executable)
//TODO: add num_of_cmd in struct & double-check the logic whenever num_node_ver is used

void	write_to_fd(t_cmd_param *cmd_p, int num_node_ver, int i, int k, int fd)
{
	int	tmp_k;

	tmp_k = k;
	while (cmd_p->exec_args[k])
	{
		write(fd, cmd_p->exec_args[k], ft_strlen(cmd_p->exec_args[k]));
		if ((k + 1) != num_node_ver && cmd_p->exec_args[k + 1] != NULL)
			write(fd, " ", 1);
		k++;
	}
	if (tmp_k == 1)
		write(fd, "\n", 1);
}

void	decide_fd(t_cmd_param *cmd_p, int num_node_ver, int num_node_hor, int i, int k)
{
	if (cmd_p->output_fd != 1)
		write_to_fd(cmd_p, num_node_ver, i, k, cmd_p->output_fd);
	else if (num_node_hor > i + 1)
		write_to_fd(cmd_p, num_node_ver, i, k, cmd_p->p[i][1]);
	else
		write_to_fd(cmd_p, num_node_ver, i, k, 1);
}

void	exec_echo(t_cmd_param *cmd_p, int num_node_ver, int num_node_hor, int i)
{
	if (num_node_ver == 1) //TODO: have to change. ex) echo > a
		printf("\n");
	else
	{
		if (ft_strlen(cmd_p->exec_args[1]) == 2 && ft_strncmp(cmd_p->exec_args[1], "-n", 2) == 0)
			decide_fd(cmd_p, num_node_ver, num_node_hor, i, 2);
		else
			decide_fd(cmd_p, num_node_ver, num_node_hor, i, 1);
	}
}
