#include "../../minishell.h"

void	cmd_env(t_cmd *cmd, t_env *env, int fd)
{
	int	k;

	k = 0;
	while (env->current_envp[k] != NULL)
	{
		if (is_exist_in_env(env->first_envp, env->current_envp[k]) == 1)
		{
			write(fd, env->current_envp[k], ft_strlen(env->current_envp[k]));
			write(fd, "\n", 1);
		}
		k++;
	}
}

void	exec_env(t_cmd *cmd, t_env *env, int i)
{
	if (cmd->num_of_args == 1)
		cmd_env(cmd, env, get_output_fd(cmd, env, i));
	else
	{
		printf("env: %s: No such file or directory\n", cmd->exec_args[1]);
		env->status_code = 127;
	}
}
