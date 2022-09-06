#include "../minishell.h"

//TODO: error handle
void	handle_error_arrows(char *str, t_env *env, t_cmd *cmd, int status_code)
{
	printf("%s\n", str);
	env->status_code = status_code;
	cmd->is_error = 1;
}

t_list	*single_right_arrow(t_list *list, t_cmd *cmd, t_env *env)
{
	list = list->extra;
	if (list == NULL)
		handle_error_arrows("syntax error newar unexpected token `newline'", env, cmd, 258);
	else
	{
		cmd->output_fd = open(list->str, O_CREAT | O_TRUNC | O_WRONLY, 0777);
		if (cmd->output_fd == -1)
			handle_error_arrows("Permission denied", env, cmd, 1);
		list = list->extra;
	}
	return (list);
}

t_list	*double_right_arrow(t_list *list, t_cmd *cmd, t_env *env)
{
	list = list->extra;
	if (list == NULL)
		handle_error_arrows("syntax error newar unexpected token `newline'", env, cmd, 258);
	else
	{
		cmd->output_fd = open(list->str, O_CREAT | O_APPEND | O_WRONLY, 0777);
		if (cmd->output_fd == -1)
			handle_error_arrows("Permission denied", env, cmd, 1);
		list = list->extra;
	}
	return (list);
}

t_list	*single_left_arrow(t_list *list, t_cmd *cmd, t_env *env)
{
	list = list->extra;
	if (list == NULL)
		handle_error_arrows("syntax error newar unexpected token `newline'", env, cmd, 258);
	else
	{
		cmd->input_fd = open(list->str, O_RDONLY); //TODO: fix
		if (access(list->str, F_OK) == -1)
			printf("%s: No such file or directory\n",list->str);
		else if (cmd->input_fd == -1)
			handle_error_arrows("Permission denied", env, cmd, 1);
		list = list->extra;
	}
	return (list);
}

t_list	*double_left_arrow(t_list *list, t_cmd *cmd, t_env *env)
{
	char	*str;
	char	*limit_str;

	list = list->extra;
	if (list == NULL)
		handle_error_arrows("syntax error newar unexpected token `newline'", env, cmd, 258);
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
	return (list);
}

t_list	*check_arrows(t_list *list, t_cmd *cmd, t_env *env)
{
	if (ft_strncmp(list->str, ">", 2) == 0)
		list = single_right_arrow(list, cmd, env);
	else if (ft_strncmp(list->str, ">>", 3) == 0)
		list = double_right_arrow(list, cmd, env);
	else if (ft_strncmp(list->str, "<", 2) == 0)
		list = single_left_arrow(list, cmd, env);
	else if (ft_strncmp(list->str, "<<", 3) == 0)
		list = double_left_arrow(list, cmd, env);
	return (list);
}
