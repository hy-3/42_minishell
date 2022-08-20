#include "minishell.h"

//TODO: implement this method (printf is temporary).
//TODO: Check below cases.
// - if begin is >/>> & one arg: > a	-> no prompt but wait list from user
// - if contains << anywhere			-> heredoc> : can I throw error if there are not enough params?
void	deal_non_cmd(int condition, t_list *list)
{
	if (condition == 2)
		printf("deal with <\n");
	if (condition == 3)
		printf("deal with <<\n");
	if (condition == 4)
		printf("deal with >\n");
	if (condition == 5)
		printf("deal with >>\n");
	if (condition == 6)
		printf("deal with double quote\n");
	if (condition == 7)
		printf("deal with single quote\n");
	if (condition == 8)
		printf("deal with $... ($ at the beginning)\n");
	if (condition == 9)
		printf("deal with ..$... ($ somewhere and not the beginning)\n");
}

int	is_cmd(t_list *list)
{
	// Deal with arrow
	if (ft_strlen(list->str) == 1 && list->str[0] == '<')
		return (2);
	if (ft_strlen(list->str) == 2 && list->str[0] == '<' && list->str[1] == '<')
		return (3);
	if (ft_strlen(list->str) == 1 && list->str[0] == '>')
		return (4);
	if (ft_strlen(list->str) == 2 && list->str[0] == '>' && list->str[1] == '>')
		return (5);
	// Deal with (double & single) quote
	if (ft_strchr(list->str, 34) != NULL)
		return (6);
	if (ft_strchr(list->str, 39) != NULL)
		return (7);
	// Deal with $ sign
	if (list->str[0] == '$')
		return (8);
	if (ft_strchr(list->str, '$') != NULL)
		return (9);
	return (1);
}

int	count_listsize(t_list *list)
{
	t_list	*prev_node;
	int		list_size;

	list_size = 0;
	while (list != NULL)
	{
		prev_node = list;
		list = list->next;
		list_size++;
	}
	return (list_size);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*prompt;
	char	*original_str;
	t_list	*list;
	int		condition;
	int		list_size;

	prompt = "minishell> ";
	while (1)
	{
		original_str = readline(prompt);
		//TODO: add history
		list = parse(original_str);
		free(original_str);
		if (list == NULL)
			continue ;
		condition = is_cmd(list);
		if (condition == 1)
		{
			//TODO: Implement check contents of list, before omitting pipe. ex) ls | | wc -> gives error
			list_size = count_listsize(list);
			pipex(list, envp, list_size);
		}
		else
			deal_non_cmd(condition, list); //TODO: implement

		/* --- to check args --- */
		int i = 0;
		printf("=====\n");
		while (list != NULL)
		{
			printf("%i: %s.", i, list->str);
			printf("\n");
			list = list->next;
			i++;
		}
		printf("=====\n");
		/* ---------------- */

	}
}