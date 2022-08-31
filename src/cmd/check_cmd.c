#include "../minishell.h"

char	*create_cmd_path(char *each_path, char *cmd)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(each_path, "/");
	res = ft_strjoin(tmp, cmd);
	free(tmp);
	return (res);
}

char	*check_f_and_x(char	*cmd, char **each_path)
{
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
		{
			cust_free(each_path);
			free(each_path);
			return (cmd);
		}
		else
			cust_perror("command not executable", 126);
	}
	return (NULL);
}

char	*is_cmd_exist_and_executable(char *path_env, char *cmd)
{
	int		n;
	char	**each_path;
	char	*cmd_path;
	char	*res;

	n = count_num_of_str(path_env, ':');
	each_path = split_to_str(path_env, ':');
	while (0 <= --n)
	{
		res = check_f_and_x(cmd, each_path);
		if (res != NULL)
			return (res);
		cmd_path = create_cmd_path(each_path[n], cmd);
		res = check_f_and_x(cmd_path, each_path);
		if (res != NULL)
			return (res);
		free(cmd_path);
	}
	return (NULL);
}
