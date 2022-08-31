#include "../../minishell.h"

void	echo(t_cmd_param *cmd_p, int k, int fd)
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

void	exec_echo(t_cmd_param *cmd_p, t_env_param *env_p, int i)
{
	if (cmd_p->num_of_args == 1)
		write(get_output_fd(cmd_p, env_p, i), "\n", 1);
	else
	{
		if (ft_strlen(cmd_p->exec_args[1]) == 2 && ft_strncmp(cmd_p->exec_args[1], "-n", 2) == 0)
			echo(cmd_p, 2, get_output_fd(cmd_p, env_p, i));
		else
			echo(cmd_p, 1, get_output_fd(cmd_p, env_p, i));
	}
}
