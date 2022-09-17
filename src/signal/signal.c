#include "../minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
	}
	if (sig == SIGINT) //TODO: set status code of 1
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
