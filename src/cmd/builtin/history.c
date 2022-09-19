/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:02:49 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/09/19 19:11:29 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	write_each_line(int fd, char *id_str, char *str)
{
	write(fd, "  ", 2);
	write(fd, id_str, ft_strlen(id_str));
	write(fd, "  ", 2);
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

void	save_history(char *str)
{
	int		fd;
	int		id;
	char	*id_str;
	char	*each_cmd;

	fd = open(".history", O_CREAT | O_RDWR | O_APPEND, 0777);
	if (fd == -1)
		cust_write("file open error\n", 1);
	add_history(str);
	id = 1;
	while (1)
	{
		each_cmd = get_next_line(fd);
		if (each_cmd == NULL)
			break ;
		id++;
		free(each_cmd);
	}
	id_str = ft_itoa(id);
	write_each_line(fd, id_str, str);
	free(id_str);
	close(fd);
}

void	exec_history(t_cmd *cmd, t_env *env, int i)
{
	int		input_fd;
	int		output_fd;
	char	*each_cmd;

	if (cmd->num_of_args == 1)
	{
		input_fd = open(".history", O_RDONLY);
		if (input_fd == -1)
			cust_write("file open error\n", 1);
		output_fd = get_output_fd(cmd, env, i);
		while (1)
		{
			each_cmd = get_next_line(input_fd);
			if (each_cmd == NULL)
				break ;
			write(output_fd, each_cmd, ft_strlen(each_cmd));
			free(each_cmd);
		}
		close(input_fd);
	}
	else
	{
		printf("history: too many arguments\n");
		g_status_code = 1;
	}
}
