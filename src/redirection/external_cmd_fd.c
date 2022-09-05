#include "../minishell.h"

void	first_cmd_fd(t_cmd *cmd, t_env *env, int i)
{
	if (cmd->input_fd != 0)
	{
		if (dup2(cmd->input_fd, 0) == -1)
			cust_perror("Error(first_cmd: dup2 input_fd)", 1);
	}
	else if (cmd->is_heredoc == 1)
	{
		if (close(cmd->heredoc_p[1]) == -1)
			cust_perror("Error(first_cmd: close cmd->heredoc_p[1])", 1);
		if (dup2(cmd->heredoc_p[0], 0) == -1)
			cust_perror("Error(first_cmd: dup2 heredoc_p[0])", 1);
	}
	if (cmd->output_fd != 1)
	{
		if (dup2(cmd->output_fd, 1) == -1)
			cust_perror("Error(first_cmd: dup2 output_fd)", 1);
		if (close(cmd->output_fd) == -1) //TODO: check if it's necessary
			cust_perror("TEMP",1);
	}
	else if (env->num_of_next_node > 1)
	{
		if (dup2(env->p[i][1], 1) == -1)
			cust_perror("Error(first_cmd: dup2 env->p[i][1])", 1);
	}
}

void	middle_cmd_fd(t_cmd *cmd, t_env *env, int i)
{
	if (close(env->p[i - 1][1]) == -1)
		cust_perror("Error(middle_cmd: close p[i - 1][1])", 1);
	if (close(env->p[i][0]) == -1)
		cust_perror("Error(middle_cmd: close p[i][0])", 1);
	if (cmd->input_fd != 0)
	{
		if (dup2(cmd->input_fd, 0) == -1)
			cust_perror("Error(middle_cmd: dup2 input_fd)", 1);
	}
	else if (cmd->is_heredoc == 1)
	{
		if (close(cmd->heredoc_p[1]) == -1)
			cust_perror("Error(middle_cmd: close cmd->heredoc_p[1])", 1);
		if (dup2(cmd->heredoc_p[0], 0) == -1)
			cust_perror("Error(middle_cmd: dup2 heredoc_p[0])", 1);
	}
	else
	{
		if (dup2(env->p[i - 1][0], 0) == -1)
			cust_perror("Error(middle_cmd: dup2 env->p[i - 1][0])", 1);
	}
	if (cmd->output_fd != 1)
	{
		if (dup2(cmd->output_fd, 1) == -1)
			cust_perror("Error(middle_cmd: dup2 output_fd)", 1);
	}
	else
	{
		if (dup2(env->p[i][1], 1) == -1)
			cust_perror("Error(middle_cmd: dup2 env->p[i][1])", 1);
	}
}

void	last_cmd_fd(t_cmd *cmd, t_env *env, int i)
{
	if (close(env->p[i - 1][1]) == -1)
		cust_perror("Error(last_cmd: close env->p[i - 1][1])", 1);
	if (cmd->input_fd != 0)
	{
		if (dup2(cmd->input_fd, 0) == -1)
			cust_perror("Error(last_cmd: dup2 input_fd)", 1);
	}
	else if (cmd->is_heredoc == 1)
	{
		if (close(cmd->heredoc_p[1]) == -1)
			cust_perror("Error(last_cmd: close cmd->heredoc_p[1])", 1);
		if (dup2(cmd->heredoc_p[0], 0) == -1)
			cust_perror("Error(last_cmd: dup2 heredoc_p[0])", 1);
	}
	else
	{
		if (dup2(env->p[i - 1][0], 0) == -1)
			cust_perror("Error(last_cmd: dup2 env->p[i - 1][0])", 1);
	}
	if (cmd->output_fd != 1)
	{
		if (dup2(cmd->output_fd, 1) == -1)
			cust_perror("Error(last_cmd: dup2 output_fd)", 1);
	}
}

void	organize_fd(t_cmd *cmd, t_env *env, int i)
{
	if (i == 0)
		first_cmd_fd(cmd, env, i);
	else if (0 < i && i < env->num_of_next_node - 1)
		middle_cmd_fd(cmd, env, i);
	else if (0 < i && i == env->num_of_next_node - 1)
		last_cmd_fd(cmd, env, i);
}
