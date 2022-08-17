#include "minishell.h"

//TODO: implement this method (printf is temporary).
//TODO: Check below cases.
// - if begin is >/>> & one arg: > a	-> no prompt but wait imput from user
// - if contains << anywhere			-> heredoc> : can I throw error if there are not enough params?
void	deal_non_cmd(int result_of_is_cmd, t_imput *parsed_imput)
{
	if (result_of_is_cmd == 2)
		printf("deal with <\n");
	if (result_of_is_cmd == 3)
		printf("deal with <<\n");
	if (result_of_is_cmd == 4)
		printf("deal with >\n");
	if (result_of_is_cmd == 5)
		printf("deal with >>\n");
	if (result_of_is_cmd == 6)
		printf("deal with double quote\n");
	if (result_of_is_cmd == 7)
		printf("deal with single quote\n");
	if (result_of_is_cmd == 8)
		printf("deal with $... ($ at the beginning)\n");
	if (result_of_is_cmd == 9)
		printf("deal with ..$... ($ somewhere and not the beginning)\n");
}

int	is_cmd(t_imput *parsed_imput)
{
	// Deal with arrow
	if (ft_strlen(parsed_imput->str) == 1 && parsed_imput->str[0] == '<')
		return (2);
	if (ft_strlen(parsed_imput->str) == 2 && parsed_imput->str[0] == '<' && parsed_imput->str[1] == '<')
		return (3);
	if (ft_strlen(parsed_imput->str) == 1 && parsed_imput->str[0] == '>')
		return (4);
	if (ft_strlen(parsed_imput->str) == 2 && parsed_imput->str[0] == '>' && parsed_imput->str[1] == '>')
		return (5);
	// Deal with (double & single) quote
	if (ft_strchr(parsed_imput->str, 34) != NULL)
		return (6);
	if (ft_strchr(parsed_imput->str, 39) != NULL)
		return (7);
	// Deal with $ sign
	if (parsed_imput->str[0] == '$')
		return (8);
	if (ft_strchr(parsed_imput->str, '$') != NULL)
		return (9);
	return (1);
}

void	omit_pipe_from_lst(t_imput *lst)
{
	t_imput *first_lst;
	t_imput *prev_lst;

	first_lst = lst;
	while (lst != NULL)
	{
		if (lst->str[0] == '|') //TODO: check if checking str[0] is enough.
		{
			prev_lst->next = lst->next;
			free(lst->str);
			free(lst);
		}
		prev_lst = lst;
		lst = lst->next;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*prompt;
	char	*original_imput;
	t_imput	*parsed_imput;
	int		result_of_is_cmd;

	prompt = "minishell> ";
	while (1)
	{
		original_imput = readline(prompt);
		parsed_imput = parse(original_imput);
		t_imput *first_node = parsed_imput; //TODO: to check(tmp)
		free(original_imput);
		result_of_is_cmd = is_cmd(parsed_imput);
		if (result_of_is_cmd == 1)
		{
			//TODO: Implement check contents of list, before omitting pipe. ex) ls | | wc -> gives error
			omit_pipe_from_lst(parsed_imput);
			// printf("%s\n", parsed_imput->next->str); //TODO: seg fault without this line.
			// printf("-- first: s:%s, p:%p\n", (parsed_imput)->str, (parsed_imput)->str);
			// printf("-- second: s:%s, p:%p\n", (parsed_imput)->next->str, (parsed_imput)->next->str);
			pipex(&parsed_imput, envp);
		}
		else
			deal_non_cmd(result_of_is_cmd, parsed_imput);
		/* --- to check --- */
		int i = 0;
		printf("=====\n");
		while (first_node != NULL)
		{
			printf("%i: %s\n", i, first_node->str);
			first_node = first_node->next;
			i++;
		}
		printf("=====\n");
		/* ---------------- */
	}
}
