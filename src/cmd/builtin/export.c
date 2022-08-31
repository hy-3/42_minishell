#include "../../minishell.h"

void	export(t_cmd_param *cmd_p, t_env_param *env_p, int fd)
{
	int		k;
	char	*new_str;

	k = 0;
	while (env_p->current_envp[k] != NULL)
	{
		new_str = ft_strjoin("declare -x ", env_p->current_envp[k]);
		write(fd, new_str, ft_strlen(new_str)); //TODO: check if I need to add "" for values.
		write(fd, "\n", 1);
		free(new_str);
		k++;
	}
}

void	exec_export(t_cmd_param *cmd_p, t_env_param *env_p, int i)
{
	int	k;

	if (cmd_p->num_of_args == 1)
		export(cmd_p, env_p, get_output_fd(cmd_p, env_p, i));
	else
	{
		k = 1;
		while (cmd_p->exec_args[k] != NULL)
			env_p->current_envp = create_new_env_with_str(env_p->current_envp, cmd_p->exec_args[k++]);
	}
}
