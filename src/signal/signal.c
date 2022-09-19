#include "../minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGQUIT)
		rl_redisplay();
	if (sig == SIGINT) //TODO: set status code of 1
	{
		write(1, "\n", 1);
		rl_on_new_line(); //if cat/wc input, this line is not needed.
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
