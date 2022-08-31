#include "../minishell.h"

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
