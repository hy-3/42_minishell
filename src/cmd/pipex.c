#include "../minishell.h"

void	child(int *p1, int *p2, t_cmd_param *cmd_p, t_env_param *env_p, int i, int num_node_hor)
{
	char	*cmd_path;

	if (i == 0 && num_node_hor > 1)
	{
		if (dup2(p2[1], 1) == -1)
			cust_perror("Error(first_child: dup2 p1[1])", 1);
	}
	else if (0 < i && i < num_node_hor - 1)
	{
		if (close(p1[1]) == -1)
			cust_perror("Error(middle_child: close p1[1])", 1);
		if (close(p2[0]) == -1)
			cust_perror("Error(middle_child: close p2[0])", 1);
		if (dup2(p1[0], 0) == -1)
			cust_perror("Error(middle_child: dup2 p1[0])", 1);
		if (dup2(p2[1], 1) == -1)
			cust_perror("Error(middle_child: dup2 p2[1])", 1);
	}
	else if (0 < i && i == num_node_hor - 1)
	{
		if (close(p1[1]) == -1)
			cust_perror("Error(last_child: close p1[1])", 1);
		if (dup2(p1[0], 0) == -1)
			cust_perror("Error(last_child: dup2 p1[0])", 1);
	}
	cmd_path = is_cmd_exist_and_executable(env_p->pathenv, cmd_p->exec_args[0]);
	if (execve(cmd_path, cmd_p->exec_args, env_p->envp) == -1)
		cust_write("command not found\n", 127);
}

int	exec_cmd(t_list *list, t_env_param *env_p, int i, int num_node_hor)
{
	t_cmd_param	cmd_p;
	int			p[100][2]; //TODO: p[ARG_MAX][2];
	int			k;
	int			num_node_ver;
	int			num_of_child;

	num_of_child = 0;
	if (pipe(p[i + 1]) < 0) //TODO: now, not using p[0] so wasting it is not ideal
		cust_perror("Error(main: pipe p[i]", 1);
	k = 0;
	cmd_p.exec_args[k++] = list->str;
	num_node_ver = count_extra(list);
	list = list->extra;
	while (list != NULL)
	{
		cmd_p.exec_args[k++] = list->str;
		list = list->extra;
	}
	cmd_p.exec_args[num_node_ver] = NULL;
	// To run 'exit' command
	if (ft_strlen(cmd_p.exec_args[0]) == 4 && ft_strncmp(cmd_p.exec_args[0], "exit", 4) == 0)
		exit(0); //TODO: check which status code I should return.
	// To run 'cd' command
	if (ft_strlen(cmd_p.exec_args[0]) == 2 && ft_strncmp(cmd_p.exec_args[0], "cd", 2) == 0)
	{
		if (num_node_ver == 2)
			chdir(cmd_p.exec_args[1]);
		else
			cust_write("ERROR: Specify relative or absolute path\n", 1); //TODO: error handle
	}
	else // To run other commands. ex) ls, wc etc
	{
		cmd_p.pid = fork();
		if (cmd_p.pid < 0)
			cust_perror("Error(exec_cmd: fork)", 1);
		if (cmd_p.pid == 0)
			child(p[i], p[i + 1], &cmd_p, env_p, i, num_node_hor);
		if (i > 0)
			if (!((close(p[i][0]) == 0) && (close(p[i][1]) == 0)))
				cust_perror("Error(cmd: close p[i][0] or p[i][1])", 1);
		num_of_child = 1;
	}
	return (num_of_child);
}

void	cust_waitpid(int num_of_executed_cmd)
{
	while (num_of_executed_cmd-- > 0)
	{
		if (waitpid(-1, NULL, 0) == -1)
			cust_perror("Error(cust_waitpid)", 1);
	}
}

int	pipex(t_list *list, char *envp[])
{
	t_env_param	env_p;
	int			status_code; //TODO: get from last exec cmd.
	char		*pathenv;
	int			num_node_hor;
	int			num_of_child;

	status_code = 0;
	env_p.envp = envp;
	env_p.pathenv = get_value_of_pathenv(envp);
	num_node_hor = count_next(list);
	num_of_child = list_iter(list, &env_p, num_node_hor, exec_cmd);
	cust_waitpid(num_of_child);
	return (status_code);
}
