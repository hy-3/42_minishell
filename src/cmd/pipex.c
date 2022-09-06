#include "../minishell.h"

int	wexitstatus(int status)
{
	return (((status) & 0xff00) >> 8);
}

void	cust_waitpid(int num_of_executed_cmd)
{
	while (num_of_executed_cmd-- > 0)
	{
		if (waitpid(-1, NULL, 0) == -1)
			cust_perror("Error(cust_waitpid)", 1);
	}
}

void	exec_cmd(t_cmd *cmd, t_env *env, int i)
{
	if (ft_strncmp(cmd->exec_args[0], "exit", 5) == 0)
		exit(0); //TODO: check which status code I should return.
	if (ft_strncmp(cmd->exec_args[0], "echo", 5) == 0)
		exec_echo(cmd, env, i);
	else if (ft_strncmp(cmd->exec_args[0], "cd", 3) == 0)
		exec_cd(cmd, env, i);
	else if (ft_strncmp(cmd->exec_args[0], "pwd", 4) == 0)
		exec_pwd(cmd, env, i);
	else if (ft_strncmp(cmd->exec_args[0], "export", 7) == 0)
		exec_export(cmd, env, i);
	else if (ft_strncmp(cmd->exec_args[0], "unset", 6) == 0)
		exec_unset(cmd, env, i);
	else if (ft_strncmp(cmd->exec_args[0], "env", 4) == 0)
		exec_env(cmd, env, i);
	else
		exec_external_cmd(cmd, env, i);
}

void	config_execargs(t_list *list, t_cmd *cmd, t_env *env)
{
	int	k;

	cmd->input_fd = 0;
	cmd->output_fd = 1;
	cmd->is_heredoc = 0;
	cmd->pid = 0;
	cmd->is_error = 0;
	k = 0;
	while (list != NULL)
	{
		list = check_arrows(list, cmd, env);
		if (list == NULL)
			break;
		cmd->exec_args[k++] = list->str;
		list = list->extra;
	}
	cmd->exec_args[k] = NULL;
	cmd->num_of_args = k;
}

void	pipex(t_list *list, t_env *env)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *) malloc(sizeof(t_cmd));
	i = 0;
	while (list != NULL)
	{
		if (pipe(env->p[i]) < 0)
			cust_perror("Error(pipex)", 1);;
		config_execargs(list, cmd, env);
		if (cmd->is_error == 1)
			return ;
		if (cmd->num_of_args != 0 && cmd->is_error == 0)
			exec_cmd(cmd, env, i);
		list = list->next;
		i++;
	}
	if (cmd->pid != 0)
	{
		env->num_of_child--;
		if (waitpid(cmd->pid, &(env->status_code), 0) == -1)
			cust_perror("ERROR(last_cmd: waitpid)", 1);
		env->status_code = wexitstatus(env->status_code);
	}
	cust_waitpid(env->num_of_child);
}
