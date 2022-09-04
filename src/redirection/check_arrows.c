#include "../minishell.h"

t_list	*check_arrows(t_list *list, t_cmd *cmd, t_env *env, int i)
{
	char	*str;
	char	*limit_str;

	if (ft_strncmp(list->str, ">", 2) == 0)
	{
		list = list->extra;
		if (list == NULL)
		{
			printf("syntax error newar unexpected token `newline'\n"); //TODO: error handle
			env->status_code = 258;
			cmd->is_error = 1;
		}
		else
		{
			cmd->output_fd = open(list->str, O_CREAT | O_TRUNC | O_WRONLY, 0777);
			if (cmd->output_fd == -1)
			{
				printf("Permission denied\n"); //TODO: error handle
				env->status_code = 1;
				cmd->is_error = 1;
			}
			list = list->extra;
		}
	}
	else if (ft_strncmp(list->str, ">>", 3) == 0)
	{
		list = list->extra;
		if (list == NULL)
		{
			printf("syntax error newar unexpected token `newline'\n"); //TODO: error handle
			env->status_code = 258;
			cmd->is_error = 1;
		}
		else
		{
			cmd->output_fd = open(list->str, O_CREAT | O_APPEND | O_WRONLY, 0777);
			if (cmd->output_fd == -1)
			{
				printf("Permission denied\n"); //TODO: error handle
				env->status_code = 1;
				cmd->is_error = 1;
			}
			list = list->extra;
		}
	}
	else if (ft_strncmp(list->str, "<", 2) == 0)
	{
		list = list->extra;
		if (list == NULL)
		{
			printf("syntax error newar unexpected token `newline'\n"); //TODO: error handle
			env->status_code = 258;
			cmd->is_error = 1;
		}
		else
		{
			if (access(list->str, F_OK) == -1)
			{
				printf("%s: No such file or directory\n", list->str); //TODO: error handle
				env->status_code = 1;
				cmd->is_error = 1;
				return (NULL);
			}
			cmd->input_fd = open(list->str, O_RDONLY);
			if (cmd->input_fd == -1)
			{
				printf("Permission denied\n"); //TODO: error handle
				env->status_code = 1;
				cmd->is_error = 1;
			}
			list = list->extra;
		}
	}
	else if (ft_strncmp(list->str, "<<", 3) == 0)
	{
		list = list->extra;
		if (list == NULL)
		{
			printf("syntax error newar unexpected token `newline'\n"); //TODO: error handle
			env->status_code = 258;
			cmd->is_error = 1;
		}
		else
		{
			if (pipe(cmd->heredoc_p) < 0)
				cust_perror("Error(pipe: heredoc_p)", 1);
			limit_str = ft_strjoin(list->str, "\n");
			while (1)
			{
				str = get_next_line(0);
				if (ft_strncmp(str, limit_str, ft_strlen(limit_str)) == 0)
					break ;
				write(cmd->heredoc_p[1], str, ft_strlen(str));
				free(str);
			}
			free(limit_str);
			cmd->is_heredoc = 1;
			list = list->extra;
		}
	}
	return (list);
}
