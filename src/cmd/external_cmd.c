#include "../minishell.h"

void	child(t_cmd_param *cmd_p, t_env_param *env_p)
{
	char	*cmd_path;

	cmd_path = is_cmd_exist_and_executable(env_p->pathenv, cmd_p->exec_args[0]);
	if (execve(cmd_path, cmd_p->exec_args, env_p->current_envp) == -1)
		cust_write("command not found\n", 127);
}

void	exec_external_cmd(t_cmd_param *cmd_p, t_env_param *env_p, int i)
{
	cmd_p->pid = fork();
	if (cmd_p->pid < 0)
		cust_perror("Error(exec_cmd: fork)", 1);
	if (cmd_p->pid == 0)
	{
		organize_fd(cmd_p, env_p, i);
		child(cmd_p, env_p);
	}
	if (cmd_p->is_heredoc == 1)
	{
		close(cmd_p->heredoc_p[0]);
		close(cmd_p->heredoc_p[1]);
	}
	if (i > 0)
		if (!((close(env_p->p[i - 1][0]) == 0) && (close(env_p->p[i - 1][1]) == 0)))
			cust_perror("Error(cmd: close cmd_p->p[i][0] or cmd_p->p[i][1])", 1);
	env_p->num_of_child += 1;
}