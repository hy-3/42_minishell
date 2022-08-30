#include "../minishell.h"

//TODO: check every builtins to work with output fd
//TODO: change to work together with pipe (with external executable)
void	exec_echo(t_cmd_param *cmd_p, int num_node_ver)
{
	int	i;

	if (num_node_ver == 1)
		printf("\n");
	else
	{
		if (ft_strlen(cmd_p->exec_args[1]) == 2 && ft_strncmp(cmd_p->exec_args[1], "-n", 2) == 0)
		{
			i = 2;
			while (cmd_p->exec_args[i])
			{
				printf("%s",cmd_p->exec_args[i]);
				if ((i + 1) != num_node_ver)
					printf(" ");
				i++;
			}
		}
		else
		{
			i = 1;
			if (cmd_p->output_fd != 1)
			{
				while (cmd_p->exec_args[i])
				{
					write(cmd_p->output_fd, cmd_p->exec_args[i], ft_strlen(cmd_p->exec_args[i]));
					if ((i + 1) != num_node_ver)
						write(cmd_p->output_fd, " ", 1);
					i++;
				}
				write(cmd_p->output_fd, "\n", 2);
			}
			else
			{
				dup2(cmd_p->p[0][1], 1); //TODO: think about how to pass builtin output to external executable
				while (cmd_p->exec_args[i])
				{
					printf("%s",cmd_p->exec_args[i]);
					if ((i + 1) != num_node_ver)
						printf(" ");
					i++;
				}
				printf("\n");
			}
		}
	}
}

void	exec_cd(t_cmd_param *cmd_p, int num_node_ver)
{
	if (num_node_ver == 2)
		chdir(cmd_p->exec_args[1]); //TODO: throw error if directory is not found.
	else
		cust_write("ERROR: Specify relative or absolute path\n", 1); //TODO: error handle
}

void	exec_pwd()
{
	char	path[PATH_MAX];

	getcwd(path, PATH_MAX);
	printf("%s\n", path);
}

void	exec_export(t_cmd_param *cmd_p, t_env_param *env_p, int num_node_ver)
{
	int	i;

	i = 0;
	if (num_node_ver == 1)
		while (env_p->current_envp[i] != NULL)
			printf("declare -x %s\n", env_p->current_envp[i++]); //TODO: check if I need to add "" for values.
	else
	{
		i = 1;
		while (cmd_p->exec_args[i] != NULL)
			env_p->current_envp = create_new_env_with_str(env_p->current_envp, cmd_p->exec_args[i++]);
	}
}

void	exec_unset(t_cmd_param *cmd_p, t_env_param *env_p, int num_node_ver)
{
	if (num_node_ver == 1)
		return ;
	else
		env_p->current_envp = upd_to_new_env(env_p, cmd_p);
}

void	exec_env(t_cmd_param *cmd_p, t_env_param *env_p, int num_node_ver)
{
	int	i;

	if (num_node_ver == 1)
	{
		i = 0;
		while (env_p->current_envp[i] != NULL)
		{
			if (is_exist_in_env(env_p->first_envp, env_p->current_envp[i]) == 1)
				printf("%s\n", env_p->current_envp[i]);
			i++;
		}
	}
	else
		printf("tmp\n"); //TODO: check what should I implement when 'env' has args.
}

void	organize_stdinout(t_cmd_param *cmd_p, int i, int num_node_hor)
{
	if (i == 0) //first cmd
	{
		if (cmd_p->input_fd != 0)
		{
			if (dup2(cmd_p->input_fd, 0) == -1)
				cust_perror("Error(first_child: dup2 input_fd)", 1);
		}
		else if (cmd_p->is_heredoc == 1) //TODO: fix heredoc
		{
			if (dup2(cmd_p->p[i][0], 0) == -1)
				cust_perror("Error(first_child: dup2 p[i][0])", 1);
		}
		if (cmd_p->output_fd != 1)
		{
			if (dup2(cmd_p->output_fd, 1) == -1)
				cust_perror("Error(first_child: dup2 output_fd)", 1);
			if (close(cmd_p->output_fd) == -1) //TODO: check if it's necessary
				cust_perror("TEMP",1);
		}
		else if (num_node_hor > 1)
		{
			if (dup2(cmd_p->p[i][1], 1) == -1)
				cust_perror("Error(first_child: dup2 p2[1])", 1);
		}
	}
	else if (0 < i && i < num_node_hor - 1) //middle cmd
	{
		if (close(cmd_p->p[i-1][1]) == -1)
			cust_perror("Error(middle_child: close p1[1])", 1);
		if (close(cmd_p->p[i][0]) == -1)
			cust_perror("Error(middle_child: close p2[0])", 1);
		if (cmd_p->input_fd != 0)
		{
			if (dup2(cmd_p->input_fd, 0) == -1)
				cust_perror("Error(first_child: dup2 input_fd)", 1);
		}
		else
		{
			if (dup2(cmd_p->p[i-1][0], 0) == -1)
				cust_perror("Error(middle_child: dup2 p1[0])", 1);
		}
		if (cmd_p->output_fd != 1)
		{
			if (dup2(cmd_p->output_fd, 1) == -1)
				cust_perror("Error(middle_child: dup2 output_fd)", 1);
		}
		else
		{
			if (dup2(cmd_p->p[i][1], 1) == -1)
				cust_perror("Error(middle_child: dup2 p2[1])", 1);
		}
	}
	else if (0 < i && i == num_node_hor - 1) //last cmd
	{
		if (close(cmd_p->p[i-1][1]) == -1)
			cust_perror("Error(last_child: close p1[1])", 1);
		if (cmd_p->output_fd != 1)
		{
			if (dup2(cmd_p->output_fd, 1) == -1)
				cust_perror("Error(last_child: dup2 output_fd)", 1);
		}
		if (cmd_p->input_fd != 0)
		{
			if (dup2(cmd_p->input_fd, 0) == -1)
				cust_perror("Error(last_child: dup2 input_fd)", 1);
		}
		else
		{
			if (dup2(cmd_p->p[i-1][0], 0) == -1)
				cust_perror("Error(last_child: dup2 p1[0])", 1);
		}
	}
}

void	exec_external_executable(t_cmd_param *cmd_p, t_env_param *env_p)
{
	char	*cmd_path;

	cmd_path = is_cmd_exist_and_executable(env_p->pathenv, cmd_p->exec_args[0]);
	if (execve(cmd_path, cmd_p->exec_args, env_p->current_envp) == -1)
		cust_write("command not found\n", 127);
}

void	exec_basedon_cmdtype(t_cmd_param *cmd_p, t_env_param *env_p, int num_node_ver, int num_node_hor, int i)
{
	if (ft_strlen(cmd_p->exec_args[0]) == 4 && ft_strncmp(cmd_p->exec_args[0], "exit", 4) == 0) //TODO: consider ft_strncmp
		exit(0); //TODO: check which status code I should return.
	if (ft_strlen(cmd_p->exec_args[0]) == 4 && ft_strncmp(cmd_p->exec_args[0], "echo", 4) == 0)
		exec_echo(cmd_p, num_node_ver);
	else if (ft_strlen(cmd_p->exec_args[0]) == 2 && ft_strncmp(cmd_p->exec_args[0], "cd", 2) == 0)
		exec_cd(cmd_p, num_node_ver);
	else if (ft_strlen(cmd_p->exec_args[0]) == 3 && ft_strncmp(cmd_p->exec_args[0], "pwd", 3) == 0)
		exec_pwd();
	else if (ft_strlen(cmd_p->exec_args[0]) == 6 && ft_strncmp(cmd_p->exec_args[0], "export", 6) == 0)
		exec_export(cmd_p, env_p, num_node_ver);
	else if (ft_strlen(cmd_p->exec_args[0]) == 5 && ft_strncmp(cmd_p->exec_args[0], "unset", 5) == 0)
		exec_unset(cmd_p, env_p, num_node_ver);
	else if (ft_strlen(cmd_p->exec_args[0]) == 3 && ft_strncmp(cmd_p->exec_args[0], "env", 3) == 0)
		exec_env(cmd_p, env_p, num_node_ver);
	else
	{
		cmd_p->pid = fork();
		if (cmd_p->pid < 0)
			cust_perror("Error(exec_cmd: fork)", 1);
		if (cmd_p->pid == 0)
		{
			organize_stdinout(cmd_p, i, num_node_hor);
			exec_external_executable(cmd_p, env_p);
		}
		if (i > 0)
			if (!((close(cmd_p->p[i-1][0]) == 0) && (close(cmd_p->p[i-1][1]) == 0)))
				cust_perror("Error(cmd: close cmd_p->p[i][0] or cmd_p->p[i][1])", 1);
		cmd_p->num_of_child += 1;
	}
}
