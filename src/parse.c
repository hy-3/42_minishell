#include "minishell.h"

t_list *create_next_node(t_list *list, int count)
{
	if (count == 0)
	{
		list = (t_list *) malloc(sizeof(t_list));
		if (list == NULL)
			printf("malloc failed\n"); //TODO: error handle
		list->extra = NULL;
		list->next = NULL;
	}
	else
	{
		list->next = (t_list *) malloc(sizeof(t_list));
		if (list->next == NULL)
			printf("malloc failed\n"); //TODO: error handle
		list = list->next;
		list->extra = NULL;
		list->next = NULL;
	}
	return (list);
}

t_list *create_extra_node(t_list *list)
{
	list->extra = (t_list *) malloc(sizeof(t_list));
	if (list->extra == NULL)
		printf("malloc failed\n"); //TODO: error handle
	list = list->extra;
	list->extra = NULL;
	list->next = NULL;
	return (list);
}

void	fill_str(char *original_str, t_list *list, int start, int i)
{
	int		k;
	char	tmp_quote;
	char	*tmp_str;
	int		count;
	t_list	*extra;

	count = 0;
	while ((i - start) > 0)
	{
		k = 0;
		while (original_str[start] == ' ')
			start++;
		if (original_str[start] == '|' || original_str[start] == '\0')
			break ;
		tmp_str = (char *) malloc((i - start + 1) * sizeof(char));
		if (tmp_str == NULL)
			printf("malloc failed\n"); //TODO: error handle
		while (original_str[start] != ' ' && original_str[start] != '\0')
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
		if (count != 0)
			list = create_extra_node(list);
		list->str = ft_strdup(tmp_str);
		free(tmp_str);
		count++;
	}
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
				list = create_next_node(list, count);
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
	list = create_next_node(list, count);
	if (count == 0)
		first_node = list;
	fill_str(original_str, list, start, i);
	return (first_node);
}

//TODO: fix
/*
$ minishell> ls|wc
command not found
wc: UH���\rS�1`H�=��-`]�<�\001: open: No such file or directory
//=====
---
node[0]:ls|wc.
---
---
node[1]:wc.
---
=====//

$ minishell> ls -l | wc
       6
$ ls -l | wc
       6      47     285
*/