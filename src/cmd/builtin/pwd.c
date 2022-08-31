#include "../../minishell.h"

void	exec_pwd(t_cmd_param *cmd_p, t_env_param *env_p, int i)
{
	char	path[PATH_MAX];
	char	*new_path;

	getcwd(path, PATH_MAX);
	new_path = ft_strjoin(path, "\n");
	write(get_output_fd(cmd_p, env_p, i), new_path, ft_strlen(new_path));
	free(new_path);
}
