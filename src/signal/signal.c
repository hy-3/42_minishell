/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:05:43 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/09/19 18:40:25 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGQUIT)
		rl_redisplay();
	if (sig == SIGINT) //TODO: set status code of 1
	{
		write(1, "\n", 1);
		rl_on_new_line(); //TODO: if cat/wc input, this line is not needed.
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	change_terminal_setting(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}
