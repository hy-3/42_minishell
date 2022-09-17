#include "../../minishell.h"

int	is_numbers(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	exec_exit(t_cmd *cmd, t_env *env, int i)
{
	int	arg;

	if (i == 0)
	{
		if (cmd->num_of_args == 1)
			exit(1);
		else
		{
			if (is_numbers(cmd->exec_args[1]) == 0)
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
					exit(256 + arg % 256);
			}
			else
			{
				printf("exit\nexit: too many arguments\n");
				env->status_code = 1;
			}
		}
	}
	else
		return ;
}