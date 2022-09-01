#include "minishell.h"

void	fill_str_allows(t_res_arrow *res, t_list *list, char *original_str, int start)
{
	int		i;
	char	*tmp_str;
	char	arrow;

	i = 0;
	arrow = original_str[start];
	if (start != 0)
		list = create_extra_node(list);
	while (original_str[start] == '>' || original_str[start] == '<')
	{
		start++;
		i++;
	}
	if (i > 2)
		printf("syntax error near unexpected token\n"); //TODO: shoudln't continue and go back prompt. error handle. bash >>> doesn't give error
	tmp_str = (char *) malloc((i + 1) * sizeof(char));
	tmp_str[0] = arrow;
	if (i == 2)
		tmp_str[1] = arrow;
	tmp_str[i] = '\0';
	list->str = ft_strdup(tmp_str);
	free(tmp_str);
	res->start = start;
	res->list = list;
}

void	fill_str(char *original_str, t_list *list, int start, int i)
{
	int			k;
	char		tmp_quote;
	char		*tmp_str;
	int			count;
	t_res_arrow	res;
	char		current_quote;
	int	end_of_dollar;

	count = 0;
	current_quote = 0;
	while ((i - start) > 0)
	{
		k = 0;
		while (original_str[start] == ' ')
			start++;
		if (original_str[start] == '|' || original_str[start] == '\0')
			break ;
		if (!(original_str[start] == '<' || original_str[start] == '>'))
		{
			tmp_str = (char *) malloc((i - start + 1) * sizeof(char));
			if (tmp_str == NULL)
				printf("malloc failed\n"); //TODO: error handle
			while (original_str[start] != ' ' && original_str[start] != '\0' && original_str[start] != '>' && original_str[start] != '<')
			{
				if (original_str[start] == '|')
					break ;
				if (original_str[start] == 34 || original_str[start] == 39)
				{
					tmp_quote = original_str[start];
					if (current_quote == 0)
						current_quote = tmp_quote;
					else
						if (current_quote == original_str[start])
							current_quote = 0;
					while (original_str[++start] != tmp_quote)
					{
						if (original_str[start] == '\0')
							cust_write("ERROR: quote is not closed.\n", 1); //TODO: error handling(check exit code.)
						tmp_str[k++] = original_str[start];
					}
					end_of_dollar = k;
					start++;
					continue ;
				}
				tmp_str[k++] = original_str[start++];
			}
			tmp_str[k] = '\0';
			if (count != 0)
				list = create_extra_node(list);
			if (is_dollar_exist(tmp_str) == 1 && (current_quote == 0 || current_quote == 34))
				list->str = convert_str_from_dollar(tmp_str, current_quote, end_of_dollar);
			else
				list->str = ft_strdup(tmp_str);
			free(tmp_str);
		}
		if (original_str[start] == '>' || original_str[start] == '<')
		{
			fill_str_allows(&res, list, original_str, start);
			start = res.start;
			list = res.list;
		}
		count++;
	}
}

int	is_nullstr_in_list(t_list *list)
{
	t_list	*prev_node;
	int		list_size;

	list_size = 0;
	while (list != NULL)
	{
		prev_node = list;
		if (list->str == NULL)
			return (1);
		list = list->next;
		list_size++;
	}
	return (0);
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
	int		k;
	int		num_of_continued_pipe;

	i = 0;
	start = i;
	count = 0;
	num_of_single_quote = 0;
	num_of_double_quote = 0;
	first_node = NULL;
	while (original_str[start] == ' ')
		start++;
	if (original_str == NULL || original_str[start] == '\0')
		return (first_node);
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
				k = i + 1;
				num_of_continued_pipe = 0;
				while (original_str[k] != '\0' && original_str[k] != ' ')
				{
					if (original_str[k] == '|')
						num_of_continued_pipe++;
					k++;
				}
				if (num_of_continued_pipe == 1)
					break ;
				if (num_of_continued_pipe > 1)
					cust_write("syntax error near unexpected token `|'\n", 1); //TODO: error handle
				list = create_next_node(list, count);
				if (count++ == 0)
					first_node = list;
				if (i == 0)
					cust_write("syntax error near unexpected token `|'\n", 1); //TODO: error handle
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
	if (is_nullstr_in_list(first_node) == 1)
		cust_write("syntax error near unexpected token `|'\n", 1); //TODO: error handle
	return (first_node);
}
