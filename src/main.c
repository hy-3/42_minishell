#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char	*prompt;
	char	*original_imput;
	t_imput	*parsed_imput;

	parsed_imput = (t_imput *) malloc(sizeof(t_imput));
	prompt = "minishell> ";
	while (1)
	{
		original_imput = readline(prompt);
		parse(original_imput, parsed_imput);
		free(original_imput);

		/* --- to check --- */
		int i = 0;
		while (parsed_imput->next != NULL)
		{
			printf("%i: %s\n", ++i, parsed_imput->str);
			parsed_imput = parsed_imput->next;
		}
		/* --- */

	}
}
