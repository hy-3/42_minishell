#include "../minishell.h"

void	organize_fd(t_cmd_param *cmd_p, t_env_param *env_p, int i)
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
			close(cmd_p->p[i][1]);
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
		else if (env_p->num_of_next_node > 1)
		{
			if (dup2(cmd_p->p[i][1], 1) == -1)
				cust_perror("Error(first_child: dup2 p2[1])", 1);
		}
	}
	else if (0 < i && i < env_p->num_of_next_node - 1) //middle cmd
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
	else if (0 < i && i == env_p->num_of_next_node - 1) //last cmd
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
