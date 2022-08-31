#include "../../minishell.h"

void	env(t_cmd_param *cmd_p, t_env_param *env_p, int fd)
{
	int	k;

	k = 0;
	while (env_p->current_envp[k] != NULL)
	{
		if (is_exist_in_env(env_p->first_envp, env_p->current_envp[k]) == 1)
		{
			write(fd, env_p->current_envp[k], ft_strlen(env_p->current_envp[k]));
			write(fd, "\n", 1);
		}
		k++;
	}
}

void	exec_env(t_cmd_param *cmd_p, t_env_param *env_p, int i)
{
	if (cmd_p->num_of_args == 1)
		env(cmd_p, env_p, get_output_fd(cmd_p, env_p, i));
	else
		printf("No option nor arguments acceptable.\n");
}
