#include "minishell.h"

void	fill_str(char *original_str, t_list *list, int start, int i)
{
	int		k;
	char	tmp_quote;
	char	*tmp_str;

	k = 0;
	tmp_str = (char *) malloc((i - start + 1) * sizeof(char));
	if (tmp_str == NULL)
		printf("malloc failed\n"); //TODO: error handle
	while ((i - start) > 0)
	{
		if (original_str[start] == 34 || original_str[start] == 39)
		{
			tmp_quote = original_str[start];
			while (original_str[++start] != tmp_quote)
			{
				if (original_str[start] == '\0')
					cust_write("ERROR: quote is not closed.\n", 1); //TODO: error handling(check exit code.)
				tmp_str[k++] = original_str[start];
			}
			start++;
			continue ;
		}
		tmp_str[k++] = original_str[start++];
	}
	tmp_str[k] = '\0';
	list->str = ft_strtrim(tmp_str, " ");
	free(tmp_str);
}

t_list *create_node(t_list *list, int count)
{
	if (count == 0)
	{
		list = (t_list *) malloc(sizeof(t_list));
		if (list == NULL)
			printf("malloc failed\n"); //TODO: error handle
		list->next = NULL;
	}
	else
	{
		list->next = (t_list *) malloc(sizeof(t_list));
		if (list->next == NULL)
			printf("malloc failed\n"); //TODO: error handle
		list = list->next;
		list->next = NULL;
	}
	return (list);
}

t_list	*parse(char *original_str)
{
	int		i;
	int		count;
	t_list	*list;
	t_list	*first_node;
	int		num_of_single_quote;
	int		num_of_double_quote;
	int		start;

	num_of_single_quote = 0;
	num_of_double_quote = 0;
	if (original_str == NULL)
		return (NULL);
	i = 0;
	count = 0;
	first_node = NULL;
	start = i;
	while (original_str[i] != '\0')
	{
		if (original_str[i] == 39)
			num_of_single_quote++;
		if (original_str[i] == 34)
			num_of_double_quote++;
		if (original_str[i] == '|')
		{
			if (num_of_single_quote % 2 == 0 && num_of_double_quote % 2 == 0)
			{
				list = create_node(list, count);
				if (count++ == 0)
					first_node = list;
				if (i == 0)
					cust_write("syntax error near unexpected token `|'", 1); //TODO: error handle
				fill_str(original_str, list, start, i);
				i += 1;
				start = i;
			}
			else
				i++;
		}
		else
			i++;
	}
	list = create_node(list, count);
	if (count++ == 0)
		first_node = list;
	fill_str(original_str, list, start, i);
	return (first_node);
}

//TODO: fix
/*
0.
Execcmd -> differenciate between no quote and with quote
ex) ls -l & "ls -l"
ex) ls "Makefile  a" b

1.
$ minishell> "ls "
Makefile        lib             minishell       src             todo.md

$ "ls "
bash: ls : command not found

-> should change to 'command not found'

2.
$ minishell> ls -l | wc
command not found
       0       0       0
=====
0: ls 
1: -l 
2: wc
=====
*/