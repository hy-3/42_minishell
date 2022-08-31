#include "../../minishell.h"

void	write_to_fd(t_cmd_param *cmd_p, int i, int k, int fd)
{
	int	tmp_k;

	tmp_k = k;
	while (cmd_p->exec_args[k])
	{
		write(fd, cmd_p->exec_args[k], ft_strlen(cmd_p->exec_args[k]));
		if ((k + 1) != cmd_p->num_of_args && cmd_p->exec_args[k + 1] != NULL)
			write(fd, " ", 1);
		k++;
	}
	if (tmp_k == 1)
		write(fd, "\n", 1);
}

void	decide_fd(t_cmd_param *cmd_p, t_env_param *env_p, int i, int k)
{
	if (cmd_p->output_fd != 1)
		write_to_fd(cmd_p, i, k, cmd_p->output_fd);
	else if (env_p->num_of_next_node > i + 1)
		write_to_fd(cmd_p, i, k, cmd_p->p[i][1]);
	else
		write_to_fd(cmd_p, i, k, 1);
}

void	exec_echo(t_cmd_param *cmd_p, t_env_param *env_p, int i)
{
	if (cmd_p->num_of_args == 1) //TODO: have to change. ex) echo > a
		printf("\n");
	else
	{
		if (ft_strlen(cmd_p->exec_args[1]) == 2 && ft_strncmp(cmd_p->exec_args[1], "-n", 2) == 0)
			decide_fd(cmd_p, env_p, i, 2);
		else
			decide_fd(cmd_p, env_p, i, 1);
	}
}
