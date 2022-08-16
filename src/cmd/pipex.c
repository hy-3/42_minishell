#include "../minishell.h"

void	child(int *p1, int *p2, t_cmd_param *cmd_p, t_env_param *env_p, int i, int num_of_args)
{
	char	*cmd_path;

	if (i == 0)
	{
		if (dup2(p2[1], 1) == -1)
			cust_perror("Error(first_child: dup2 p1[1])", 1);
	}
	else if (0 < i && i < num_of_args - 1)
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
	else
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

void	exec_cmd(char *str, t_env_param *env_p, int i, int num_of_args)
{
	t_cmd_param	cmd_p;
	int			p[100][2]; //TODO: p[ARG_MAX][2];

	if (pipe(p[i + 1]) < 0) //TODO: now, not using p[0] so wasting it is not ideal
		cust_perror("Error(main: pipe p[i]", 1);
	cmd_p.n = count_num_of_str(str, ' ');
	cmd_p.cmd_with_option = split_to_str(str, ' ');
	if (cmd_p.cmd_with_option == NULL)
		cust_write("Error(exec_cmd): malloc failed\n", 1);
	cmd_p.exec_args[cmd_p.n] = NULL;
	while (0 <= --cmd_p.n)
		cmd_p.exec_args[cmd_p.n] = cmd_p.cmd_with_option[cmd_p.n];
	cmd_p.pid = fork();
	if (cmd_p.pid < 0)
		cust_perror("Error(exec_cmd: fork)", 1);
	if (cmd_p.pid == 0)
		child(p[i], p[i + 1], &cmd_p, env_p, i, num_of_args);
	if (i > 0)
		if (!((close(p[i][0]) == 0) && (close(p[i][1]) == 0)))
			cust_perror("Error(cmd: close p[i][0] or p[i][1])", 1);
	cust_free(cmd_p.cmd_with_option);
	free(cmd_p.cmd_with_option);
}

void	cust_waitpid(int num_of_executed_cmd)
{
	while (num_of_executed_cmd-- > 0)
	{
		if (waitpid(-1, NULL, 0) == -1)
			cust_perror("Error(cust_waitpid)", 1);
	}
}

int	pipex(t_imput **parsed_imput, char *envp[])
{
	t_env_param	*env_p;
	int			num_of_args;
	int			status_code; //TODO: get from last exec cmd.
	char		*pathenv;

	status_code = 0;
	env_p->envp = envp;
	env_p->pathenv = get_value_of_pathenv(envp);
	num_of_args = cust_lstsize(parsed_imput);
	lstiter_exec_cmd(parsed_imput, env_p, num_of_args, exec_cmd);
	cust_waitpid(num_of_args);
	return (status_code);
}
