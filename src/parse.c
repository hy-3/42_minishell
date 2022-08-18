#include "minishell.h"

int	count_char_in_onechunk(char *original_str, int i)
{
	int		num_of_single_quote;
	int		num_of_double_quote;

	num_of_single_quote = 0;
	num_of_double_quote = 0;
	while (original_str[i] != '\0')
	{
		if (original_str[i] == ' ' || original_str[i] == '|')
		{
			if (num_of_single_quote % 2 == 0 && num_of_double_quote % 2 == 0)
			{
				i++;
				break ;
			}
		}
		if (original_str[i] == 39)
			num_of_single_quote++;
		if (original_str[i] == 34)
			num_of_double_quote++;
		i++;
	}
	return (i);
}

int	fill_str(char *original_str, t_list *list, int i)
{
	int		k;
	int		start;
	char	tmp_quote;

	k = 0;
	start = i;
	i = count_char_in_onechunk(original_str, i);
	list->str = (char *) malloc((i - start + 1) * sizeof(char));
	if (list->str == NULL)
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
				list->str[k++] = original_str[start];
			}
			start++;
			continue ;
		}
		list->str[k++] = original_str[start++];
	}
	list->str[k] = '\0';
	return (i);
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

	if (original_str == NULL)
		return (NULL);
	i = 0;
	count = 0;
	first_node = NULL;
	while (original_str[i] != '\0')
	{
		if (original_str[i] != ' ')
		{
			list = create_node(list, count);
			if (count++ == 0)
				first_node = list;
			i = fill_str(original_str, list, i);
		}
		else
			i++;
	}
	return (first_node);
}

//TODO: fix
/*
minishell> '" dasf' " fadsf
ERROR: quote is not closed.
*/