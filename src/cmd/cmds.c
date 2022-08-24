#include "../minishell.h"

void exec_cd(t_cmd_param *cmd_p, int num_node_ver)
{
	if (num_node_ver == 2)
		chdir(cmd_p->exec_args[1]); // TODO: throw error if directory is not found.
	else
		cust_write("ERROR: Specify relative or absolute path\n", 1); // TODO: error handle
}

void exec_pwd()
{
	char path[PATH_MAX];

	char str[PATH_MAX + 1];
	printf("%s\n", getcwd(str, PATH_MAX));
}

void exec_env(char **env)
{
	while (*env)
		printf("%s\n", *env++);
}
// TODO
void exec_exit(int n)
{
	exit(0);
}

// TODO: implement
void exec_export(t_cmd_param *cmd_p, t_env_param *env_p, int num_node_ver)
{
	int i;
	int k;

	i = 0;
	if (num_node_ver == 1)
	{
		while (env_p->envp[i] != NULL)
		{
			printf("%s=%s\n", env_p->envp[i], getenv(env_p->envp[i])); // TODO: not sure if I need to do an alpabetic order
			i++;
		}
	}
	else
	{
		k = 0;
		while (env_p->envp[k] != NULL)
			k++;
		i = 1;
		while (cmd_p->exec_args[i] != NULL)
		{
			env_p->envp[k++] = cmd_p->exec_args[i++];
			env_p->envp[k] = NULL;
		}
	}
}

// TODO: implement
void exec_unset()
{
	printf("TEMP:unset\n");
}

void child(int *p1, int *p2, t_cmd_param *cmd_p, t_env_param *env_p, int i, int num_node_hor)
{
	char *cmd_path;

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

void exec_other_cmd(t_cmd_param *cmd_p, t_env_param *env_p, int num_node_hor, int i)
{
	int p[100][2]; // TODO: p[ARG_MAX][2];

	if (pipe(p[i + 1]) < 0) // TODO: now, not using p[0] so wasting it is not ideal
		cust_perror("Error(main: pipe p[i]", 1);
	cmd_p->pid = fork();
	if (cmd_p->pid < 0)
		cust_perror("Error(exec_cmd: fork)", 1);
	if (cmd_p->pid == 0)
		child(p[i], p[i + 1], cmd_p, env_p, i, num_node_hor);
	if (i > 0)
		if (!((close(p[i][0]) == 0) && (close(p[i][1]) == 0)))
			cust_perror("Error(cmd: close p[i][0] or p[i][1])", 1);
}

int exec_basedon_cmdtype(t_cmd_param *cmd_p, t_env_param *env_p, int num_node_ver, int num_node_hor, int i)
{
	int num_of_child;

	num_of_child = 0;
	if (ft_strlen(cmd_p->exec_args[0]) == 4 && ft_strncmp(cmd_p->exec_args[0], "exit", 4) == 0)
		exit(0); // TODO: check which status code I should return.
	if (ft_strlen(cmd_p->exec_args[0]) == 2 && ft_strncmp(cmd_p->exec_args[0], "cd", 2) == 0)
		exec_cd(cmd_p, num_node_ver);
	else if (ft_strlen(cmd_p->exec_args[0]) == 3 && ft_strncmp(cmd_p->exec_args[0], "pwd", 3) == 0)
		exec_pwd();
	else if (ft_strlen(cmd_p->exec_args[0]) == 3 && ft_strncmp(cmd_p->exec_args[0], "env", 3) == 0)
		exec_env(env_p->envp);
	else if (ft_strlen(cmd_p->exec_args[0]) == 6 && ft_strncmp(cmd_p->exec_args[0], "export", 6) == 0)
		exec_export(cmd_p, env_p, num_node_ver);
	else if (ft_strlen(cmd_p->exec_args[0]) == 5 && ft_strncmp(cmd_p->exec_args[0], "unset", 5) == 0)
		exec_unset();
	else
	{
		exec_other_cmd(cmd_p, env_p, num_node_hor, i);
		num_of_child = 1;
	}
	return (num_of_child);
}
