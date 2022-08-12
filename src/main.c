#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char	*prompt;
	char	*str;

	prompt = "minishell> ";
	while (1)
	{
		str = readline(prompt);
		free(str);
	}
}
