#include "../minishell.h"

void	organize_fd(t_cmd_param *cmd_p, t_env_param *env_p, int i)
{
	if (i == 0)
	{
		if (cmd_p->input_fd != 0)
		{
			if (dup2(cmd_p->input_fd, 0) == -1)
				cust_perror("Error(first_cmd: dup2 input_fd)", 1);
		}
		else if (cmd_p->is_heredoc == 1)
		{
			if (close(cmd_p->heredoc_p[1]) == -1)
				cust_perror("Error(first_cmd: close cmd_p->heredoc_p[1])", 1);
			if (dup2(cmd_p->heredoc_p[0], 0) == -1)
				cust_perror("Error(first_cmd: dup2 heredoc_p[0])", 1);
		}
		if (cmd_p->output_fd != 1)
		{
			if (dup2(cmd_p->output_fd, 1) == -1)
				cust_perror("Error(first_cmd: dup2 output_fd)", 1);
			if (close(cmd_p->output_fd) == -1) //TODO: check if it's necessary
				cust_perror("TEMP",1);
		}
		else if (env_p->num_of_next_node > 1)
		{
			if (dup2(env_p->p[i][1], 1) == -1)
				cust_perror("Error(first_cmd: dup2 env_p->p[i][1])", 1);
		}
	}
	else if (0 < i && i < env_p->num_of_next_node - 1)
	{
		if (close(env_p->p[i - 1][1]) == -1)
			cust_perror("Error(middle_cmd: close p[i - 1][1])", 1);
		if (close(env_p->p[i][0]) == -1)
			cust_perror("Error(middle_cmd: close p[i][0])", 1);
		if (cmd_p->input_fd != 0)
		{
			if (dup2(cmd_p->input_fd, 0) == -1)
				cust_perror("Error(middle_cmd: dup2 input_fd)", 1);
		}
		else if (cmd_p->is_heredoc == 1)
		{
			if (close(cmd_p->heredoc_p[1]) == -1)
				cust_perror("Error(middle_cmd: close cmd_p->heredoc_p[1])", 1);
			if (dup2(cmd_p->heredoc_p[0], 0) == -1)
				cust_perror("Error(middle_cmd: dup2 heredoc_p[0])", 1);
		}
		else
		{
			if (dup2(env_p->p[i - 1][0], 0) == -1)
				cust_perror("Error(middle_cmd: dup2 env_p->p[i - 1][0])", 1);
		}
		if (cmd_p->output_fd != 1)
		{
			if (dup2(cmd_p->output_fd, 1) == -1)
				cust_perror("Error(middle_cmd: dup2 output_fd)", 1);
		}
		else
		{
			if (dup2(env_p->p[i][1], 1) == -1)
				cust_perror("Error(middle_cmd: dup2 env_p->p[i][1])", 1);
		}
	}
	else if (0 < i && i == env_p->num_of_next_node - 1)
	{
		if (close(env_p->p[i - 1][1]) == -1)
			cust_perror("Error(last_cmd: close env_p->p[i - 1][1])", 1);
		if (cmd_p->input_fd != 0)
		{
			if (dup2(cmd_p->input_fd, 0) == -1)
				cust_perror("Error(last_cmd: dup2 input_fd)", 1);
		}
		else if (cmd_p->is_heredoc == 1)
		{
			if (close(cmd_p->heredoc_p[1]) == -1)
				cust_perror("Error(last_cmd: close cmd_p->heredoc_p[1])", 1);
			if (dup2(cmd_p->heredoc_p[0], 0) == -1)
				cust_perror("Error(last_cmd: dup2 heredoc_p[0])", 1);
		}
		else
		{
			if (dup2(env_p->p[i - 1][0], 0) == -1)
				cust_perror("Error(last_cmd: dup2 env_p->p[i - 1][0])", 1);
		}
		if (cmd_p->output_fd != 1)
		{
			if (dup2(cmd_p->output_fd, 1) == -1)
				cust_perror("Error(last_cmd: dup2 output_fd)", 1);
		}
	}
}
