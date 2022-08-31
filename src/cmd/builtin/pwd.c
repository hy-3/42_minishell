#include "../../minishell.h"

//TODO: check every builtins to work with output fd
//TODO: change to work together with pipe (with external executable)

void	exec_pwd()
{
	char	path[PATH_MAX];

	getcwd(path, PATH_MAX);
	printf("%s\n", path);
}
