/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:05:43 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/09/19 19:12:51 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrlc_handler(int sig)
{
	extern int	rl_done;

	sig = 0;
	if (g_condition == 1)
	{
		rl_done = 1;
		rl_replace_line("", 0);
		rl_redisplay();
		g_condition = -1;
	}
	else
	{
		if (g_condition == 2)
			g_condition = -2;
		else
		{
			g_condition = -1;
			rl_on_new_line();
		}
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ctrlslash_handler(int sig)
{
	sig = 0;
	if (g_condition == 2)
	{
		g_condition = -3;
		printf("Quit: 3\n");
	}
	else
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

int	readline_event(void)
{
	return (0);
}

void	handle_signals(void)
{
	struct sigaction	ctrlc;
	struct sigaction	ctrlslash;
	extern int			(*rl_event_hook)(void);

	rl_event_hook = readline_event;
	ctrlc.sa_handler = ctrlc_handler;
	ctrlslash.sa_handler = ctrlslash_handler;
	sigaction(SIGINT, &ctrlc, NULL);
	sigaction(SIGQUIT, &ctrlslash, NULL);
}

void	change_terminal_setting(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}
