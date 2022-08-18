#include "minishell.h"

t_list	*parse(char *original_str)
{
	int		i;
	int		k;
	int		start;
	t_list	*list;
	t_list	*first_node;
	int		num_of_single_quote;
	int		num_of_double_quote;
	char 	tmp_quote;
	int		count;

	if (original_str == NULL)
		return (NULL);
	i = 0;
	count = 0;
	first_node = NULL;
	while (original_str[i] != '\0')
	{
		if (original_str[i] != ' ')
		{
			if (count++ == 0)
			{
				list = (t_list *) malloc(sizeof(t_list));
				list->next = NULL;
				// if (list == NULL)
					//TODO: error handle
				first_node = list;
			}
			else
			{
				list->next = (t_list *) malloc(sizeof(t_list));
				list = list->next;
				list->next = NULL;
			}
			start = i;
			num_of_single_quote = 0;
			num_of_double_quote = 0;
			while (((num_of_single_quote > 0 || num_of_double_quote > 0) && original_str[i] != '\0') || (original_str[i] != ' ' && original_str[i] != '\0'))
			{
				if (original_str[i] == 34)
					num_of_double_quote++;
				if (original_str[i] == 39)
					num_of_single_quote++;
				if (original_str[i] == '|' && (num_of_double_quote % 2 != 0 || num_of_single_quote % 2 != 0))
				{
					i++;
					continue ;
				}
				if (original_str[i] == '|' && (num_of_double_quote % 2 == 0 && num_of_single_quote % 2 == 0))
				{
					if (start == i)
						i++;
					break ;
				}
				i++;
			}
			list->str = (char *) malloc((i - start + 1) * sizeof(char));
			// if (list->str == NULL)
				//TODO: error handle
			k = 0;
			while ((i - start) > 0)
			{
				if (original_str[start] == 34 || original_str[start] == 39)
				{
					tmp_quote = original_str[start++];
					while (original_str[start] != tmp_quote)
					{
						if (original_str[start] == '\0')
						{
							printf("ERROR: quote is not closed.\n");
							exit(1); //TODO: error handling
						}
						list->str[k++] = original_str[start++];
					}
					start++;
					continue;
				}
				list->str[k++] = original_str[start++];
			}
			list->str[k] = '\0';
		}
		else
			i++;
	}
	return (first_node);
}
