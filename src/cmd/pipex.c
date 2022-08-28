#include "../minishell.h"

void	cust_waitpid(int num_of_executed_cmd)
{
	while (num_of_executed_cmd-- > 0)
	{
		if (waitpid(-1, NULL, 0) == -1)
			cust_perror("Error(cust_waitpid)", 1);
	}
}

t_list	*check_arrows(t_list *list, t_cmd_param *cmd_p)
{
	if (ft_strchr(list->str, '>') != NULL)
	{
		list = list->extra;
		if (list == NULL)
			printf("syntax error newar unexpected token `newline'\n"); //TODO: error handle.
		else
		{
			cmd_p->output_fd = open(list->str, O_CREAT | O_TRUNC | O_WRONLY, 0777);
			list = list->extra;
		}
	}
	else if (ft_strnstr(list->str, ">>", ft_strlen(list->str)) != NULL)
	{
		list = list->extra;
		if (list == NULL)
			printf("syntax error newar unexpected token `newline'\n"); //TODO: error handle.
		else
		{
			cmd_p->output_fd = open(list->str, O_CREAT | O_APPEND | O_WRONLY, 0777);
			list = list->extra;
		}
	}
	else if (ft_strchr(list->str, '<') != NULL)
	{

	}
	else if (ft_strnstr(list->str, "<<", ft_strlen(list->str)) != NULL)
	{

	}
	return (list);
}

int	exec_cmd(t_list *list, t_env_param *env_p, int i, int num_node_hor)
{
	t_cmd_param	cmd_p;
	int			k;
	int			num_node_ver;

	cmd_p.input_fd = 0;
	cmd_p.output_fd = 1;
	k = 0;
	num_node_ver = count_extra_node(list);
	while (list != NULL)
	{
		list = check_arrows(list, &cmd_p);
		if (list == NULL)
			break;
		cmd_p.exec_args[k++] = list->str;
		list = list->extra;
	}
	if (k == 0)
		return (0);
	cmd_p.exec_args[num_node_ver] = NULL;
	return (exec_basedon_cmdtype(&cmd_p, env_p, num_node_ver, num_node_hor, i));
}

int	pipex(t_list *list, t_env_param *env_p)
{
	int			status_code; //TODO: get from last exec cmd.
	char		*pathenv;
	int			num_node_hor;
	int			num_of_child;

	status_code = 0;
	num_node_hor = count_next_node(list);
	num_of_child = list_iter(list, env_p, num_node_hor, exec_cmd);
	cust_waitpid(num_of_child);
	return (status_code);
}
