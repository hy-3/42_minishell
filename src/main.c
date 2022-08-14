#include "minishell.h"

//TODO: Check below cases.
// - if begin is >/>> & one arg: > a	-> no prompt but wait imput from user
// - if contains << anywhere			-> heredoc> : can I throw error if there are not enough params?
int	main(int argc, char *argv[], char *env[])
{
	char	*prompt;
	char	*original_imput;
	t_imput	*parsed_imput;

	prompt = "minishell> ";
	while (1)
	{
		original_imput = readline(prompt);
		parsed_imput = parse(original_imput);
		free(original_imput);

		/* --- to check --- */
		int i = 0;
		while (parsed_imput->next != NULL)
		{
			printf("%i: %s\n", i, parsed_imput->str);
			parsed_imput = parsed_imput->next;
			i++;
		}
		printf("%i: %s\n", i, parsed_imput->str);
		/* ---------------- */

	}
}
