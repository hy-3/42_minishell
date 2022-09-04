#include "../../minishell.h"

void	cmd_echo(t_cmd *cmd, int k, int fd)
{
	int	tmp_k;

	tmp_k = k;
	while (cmd->exec_args[k])
	{
		write(fd, cmd->exec_args[k], ft_strlen(cmd->exec_args[k]));
		if ((k + 1) != cmd->num_of_args && cmd->exec_args[k + 1] != NULL)
			write(fd, " ", 1);
		k++;
	}
	if (tmp_k == 1)
		write(fd, "\n", 1);
}

void	exec_echo(t_cmd *cmd, t_env *env, int i)
{
	if (cmd->num_of_args == 1)
		write(get_output_fd(cmd, env, i), "\n", 1);
	else
	{
		if (ft_strlen(cmd->exec_args[1]) == 2 && ft_strncmp(cmd->exec_args[1], "-n", 2) == 0)
			cmd_echo(cmd, 2, get_output_fd(cmd, env, i));
		else
			cmd_echo(cmd, 1, get_output_fd(cmd, env, i));
	}
}
