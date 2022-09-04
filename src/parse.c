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
		if (list->str == NULL)
		{
			printf("parse error near `|'\n"); //TODO: error handle
			return (1);
		}
		list = list->next;
	}
	return (0);
}

void	upd_quote_condition(t_quote_con *quote_condition, char c, int count)
{
	if (count == 0)
	{
		quote_condition->num_of_single = 0;
		quote_condition->num_of_double = 0;
	}
	if (c == 39)
		quote_condition->num_of_single++;
	if (c == 34)
		quote_condition->num_of_double++;
	if (quote_condition->num_of_single % 2 == 0 && quote_condition->num_of_double % 2 == 0)
		quote_condition->is_closed = 1;
	else
		quote_condition->is_closed = 0;
}

int	check_pipe_num(char *original_str, int k)
{
	int	num_of_pipe;

	num_of_pipe = 1;
	while (original_str[k] != '\0' && original_str[k] != ' ')
	{
		if (original_str[k] == '|')
			num_of_pipe++;
		k++;
	}
	return (num_of_pipe);
}

int	check_pipe_condition(char *original_str, int i)
{
	int	num_of_pipe;

	num_of_pipe = 0;
	if (i == 0)
	{
		printf("parse error near `|'\n"); //TODO: error handle
		return (2);
	}
	num_of_pipe = check_pipe_num(original_str, i + 1);
	if (num_of_pipe == 2)
		return (1);
	if (num_of_pipe > 2)
	{
		printf("syntax error near unexpected token `|' (pipe continued)\n"); //TODO: error handle
		return (2);
	}
	return (0);
}

t_list	*parse(char *original_str, t_env_param *env_p)
{
	int		i;
	int		start;
	int		count;
	t_list	*list;
	t_list	*first_node;
	t_quote_con quote_condition;
	int		pipe_condition;

	i = 0;
	start = i;
	count = 0;
	first_node = NULL;
	quote_condition.is_closed = 1;
	if (original_str == NULL || original_str[start] == '\0')
		return (NULL);
	while (original_str[i] != '\0')
	{
		upd_quote_condition(&quote_condition, original_str[i], count);
		if (original_str[i] == '|')
		{
			if (quote_condition.is_closed == 1)
			{
				pipe_condition = check_pipe_condition(original_str, i);
				if (pipe_condition == 1)
					break ;
				else if (pipe_condition == 2)
					return (NULL);
				list = create_next_node(list, count);
				if (count++ == 0)
					first_node = list;
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
		return (NULL);
	return (first_node);
}
