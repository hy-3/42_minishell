#include "../../minishell.h"

int	is_all_number(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i++]) == 0)
			return (0);
	}
	return (1);
}

void	exec_exit(t_cmd *cmd, t_env *env)
{
	int	arg;

	if (cmd->num_of_args == 1)
		exit(1);
	else
	{
		if (is_all_numer(cmd->exec_args[1]) == 0)
		{
			printf("exit\nexit: %s: numeric argument required\n", cmd->exec_args[1]);
			exit(255);
		}
		arg = ft_atoi(cmd->exec_args[1]);
		if (cmd->num_of_args == 2)
		{
			if (arg > 0)
				exit(arg % 256);
			else
				exit(256 - arg % 256);
		}
		else
		{
			printf("exit\nexit: too many arguments\n");
			//TODO: stop after cmd
		}
	}
}
