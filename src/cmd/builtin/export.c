#include "../../minishell.h"

void	cmd_export(t_cmd *cmd, t_env *env, int fd)
{
	int		k;
	char	*new_str;

	k = 0;
	while (env->current_envp[k] != NULL)
	{
		new_str = ft_strjoin("declare -x ", env->current_envp[k]);
		write(fd, new_str, ft_strlen(new_str)); //TODO: check if I need to add "" for values.
		write(fd, "\n", 1);
		free(new_str);
		k++;
	}
}

void	exec_export(t_cmd *cmd, t_env *env, int i)
{
	int	k;

	if (cmd->num_of_args == 1)
		cmd_export(cmd, env, get_output_fd(cmd, env, i));
	else
	{
		k = 1;
		while (cmd->exec_args[k] != NULL)
			env->current_envp = create_new_env_with_str(env->current_envp, cmd->exec_args[k++], env);
	}
}
