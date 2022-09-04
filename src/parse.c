#include "minishell.h"

int	fill_str_allows(t_res_arrow *res, t_list *list, char *original_str, int start, int count)
{
	int		i;
	char	*tmp_str;
	char	arrow;

	i = 0;
	arrow = original_str[start];
	if (count != 0)
		list = create_extra_node(list);
	while (original_str[start] == '>' || original_str[start] == '<')
	{
		start++;
		i++;
	}
	if (i > 2) //TODO: check what to do with when three <. ex) wc <<< a
	{
		printf("syntax error near unexpected token `"); //TODO: error handle
		while (i > 2)
		{
			printf("%c", arrow);
			i--;
		}
		printf("'\n");
		return (0);
	}
	tmp_str = (char *) malloc((i + 1) * sizeof(char));
	tmp_str[0] = arrow;
	if (i == 2)
		tmp_str[1] = arrow;
	tmp_str[i] = '\0';
	list->str = ft_strdup(tmp_str);
	free(tmp_str);
	res->start = start;
	res->list = list;
	return (1);
}

int	fill_str(char *original_str, t_list *list, int start, int i, t_env_param *env_p)
{
	int			k;
	char		tmp_quote;
	char		*tmp_str;
	int			count;
	t_res_arrow	res;
	char		current_quote;
	int	end_of_dollar;

	end_of_dollar = -1;
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
						{
							printf("ERROR: quote is not closed.\n"); //TODO: error handle.
							return (0);
						}
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
				list->str = convert_str_from_dollar(tmp_str, current_quote, end_of_dollar, env_p);
			else
				list->str = ft_strdup(tmp_str);
			free(tmp_str);
		}
		if (original_str[start] == '>' || original_str[start] == '<')
		{
			if (fill_str_allows(&res, list, original_str, start, count) == 0)
				return (0);
			start = res.start;
			list = res.list;
		}
		count++;
	}
	return (1);
}

int	is_nullstr_in_list(t_list *list)
{
	while (list != NULL)
	{
		printf("##:%s\n",list->str);
		if (list->str == NULL)
			return (1);
		list = list->next;
	}
	return (0);
}

t_list	*parse(char *original_str, t_env_param *env_p)
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
	if (original_str == NULL || original_str[start] == '\0')
		return (NULL);
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
				{
					printf("syntax error near unexpected token `|' (pipe continued)\n"); //TODO: error handle
					return (NULL);
				}
				list = create_next_node(list, count);
				if (count++ == 0)
					first_node = list;
				if (i == 0)
				{
					printf("syntax error near unexpected token `|' (nothing after pipe)\n"); //TODO: error handle
					return (NULL);
				}
				fill_str(original_str, list, start, i, env_p);
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
	if (fill_str(original_str, list, start, i, env_p) == 0)
		return (NULL);
	if (is_nullstr_in_list(first_node) == 1)
	{
		printf("syntax error near unexpected token `|' (null str included)\n"); //TODO: error handle
		return (NULL);
	}
	return (first_node);
}
