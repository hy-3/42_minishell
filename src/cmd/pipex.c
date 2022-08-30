#include "../minishell.h"

void	cust_waitpid(int num_of_executed_cmd)
{
	while (num_of_executed_cmd-- > 0)
	{
		if (waitpid(-1, NULL, 0) == -1)
			cust_perror("Error(cust_waitpid)", 1);
	}
}

t_list	*check_arrows(t_list *list, t_cmd_param *cmd_p, int i)
{
	char	*str;
	char	*limit_str;

	if (ft_strlen(list->str) == 1 && ft_strchr(list->str, '>') != NULL)
	{
		list = list->extra;
		if (list == NULL)
			printf("syntax error newar unexpected token `newline'\n"); //TODO: bring back to prompt. free if it's necessary.
		else
		{
			cmd_p->output_fd = open(list->str, O_CREAT | O_TRUNC | O_WRONLY, 0777);
			if (cmd_p->output_fd == -1)
				cust_write("file open failed\n", 1); //TODO: error handle
			list = list->extra;
		}
	}
	else if (ft_strlen(list->str) == 2 && ft_strnstr(list->str, ">>", ft_strlen(list->str)) != NULL)
	{
		list = list->extra;
		if (list == NULL)
			printf("syntax error newar unexpected token `newline'\n"); //TODO: bring back to prompt. free if it's necessary.
		else
		{
			cmd_p->output_fd = open(list->str, O_CREAT | O_APPEND | O_WRONLY, 0777);
			if (cmd_p->output_fd == -1)
				cust_write("file open failed\n", 1); //TODO: error handle
			list = list->extra;
		}
	}
	else if (ft_strlen(list->str) == 1 && ft_strchr(list->str, '<') != NULL)
	{
		list = list->extra;
		if (list == NULL)
			printf("syntax error newar unexpected token `newline'\n"); //TODO: bring back to prompt. free if it's necessary.
		else
		{
			cmd_p->input_fd = open(list->str, O_RDONLY);
			if (cmd_p->input_fd == -1)
				printf("%s: No such file or directory\n", list->str); //TODO: bring back to prompt. free if it's necessary.
			list = list->extra;
		}
	}
	else if (ft_strlen(list->str) == 2 && ft_strnstr(list->str, "<<", ft_strlen(list->str)) != NULL)
	{
		list = list->extra;
		if (list == NULL)
			printf("syntax error newar unexpected token `newline'\n"); //TODO: bring back to prompt. free if it's necessary.
		else
		{
			limit_str = ft_strjoin(list->str, "\n");
			while (1)
			{
				str = get_next_line(0);
				if (ft_strncmp(str, limit_str, ft_strlen(limit_str)) == 0)
					break ;
				write(cmd_p->p[i][1], str, ft_strlen(str));
				free(str);
			}
			free(limit_str);
			cmd_p->is_heredoc = 1;
			list = list->extra;
		}
	}
	return (list);
}

void	exec_cmd(t_list *list, t_cmd_param *cmd_p, t_env_param *env_p, int i, int num_node_hor)
{
	int			k;
	int			num_node_ver;

	k = 0;
	num_node_ver = count_extra_node(list);
	while (list != NULL)
	{
		list = check_arrows(list, cmd_p, i);
		if (list == NULL)
			break;
		cmd_p->exec_args[k++] = list->str;
		list = list->extra;
	}
	if (k == 0)
		return ;
	cmd_p->exec_args[k] = NULL;
	exec_basedon_cmdtype(cmd_p, env_p, num_node_ver, num_node_hor, i);
}

int	pipex(t_list *list, t_env_param *env_p)
{
	int			status_code; //TODO: get from last exec cmd.
	char		*pathenv;
	int			num_node_hor;
	t_cmd_param	*cmd_p;
	int	i;

	cmd_p = (t_cmd_param *) malloc(sizeof(t_cmd_param));

	cmd_p->num_of_child = 0;
	status_code = 0;
	num_node_hor = count_next_node(list);
	i = 0;
	while (list != NULL)
	{
		pipe(cmd_p->p[i]);
		cmd_p->input_fd = 0;
		cmd_p->output_fd = 1;
		cmd_p->is_heredoc = 0;
		exec_cmd(list, cmd_p, env_p, i, num_node_hor);
		list = list->next;
		i++;
	}
	cust_waitpid(cmd_p->num_of_child);
	return (status_code);
}
