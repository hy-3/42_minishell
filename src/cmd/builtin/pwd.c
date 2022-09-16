#include "../../minishell.h"

void	exec_pwd(t_cmd *cmd, t_env *env, int i)
{
	char	path[PATH_MAX];
	char	*new_path;

	getcwd(path, PATH_MAX);
	new_path = ft_strjoin(path, "\n");
	write(get_output_fd(cmd, env, i), new_path, ft_strlen(new_path));
	free(new_path);
}
