#include "../minishell.h"

void	print_toomany_arrow_error(char arrow, int i)
{
	printf("syntax error near unexpected token `");
	while (i-- > 2)
		printf("%c", arrow);
	printf("'\n");
}

void	create_arrow_str(t_fill *fill, char arrow, int i)
{
	fill->tmp_str = (char *) malloc((i + 1) * sizeof(char));
	if (fill->tmp_str == NULL)
		printf("malloc failed\n"); //TODO: error handle
	fill->tmp_str[0] = arrow;
	if (i == 2)
		fill->tmp_str[1] = arrow;
	fill->tmp_str[i] = '\0';
}

void	fill_str_allows(char *original_str, t_fill *fill, t_parse *parse)
{
	int		i;
	char	arrow;

	i = 0;
	arrow = original_str[fill->start];
	if (fill->count != 0)
		fill->list = create_extra_node(fill->list);
	while (original_str[fill->start] == '>' || original_str[fill->start] == '<')
	{
		fill->start++;
		i++;
	}
	if (i > 2) //TODO: check what to do with when three <. ex) wc <<< a
	{
		print_toomany_arrow_error(arrow, i); //TODO: error handle
		parse->first_node = NULL;
		return ;
	}
	create_arrow_str(fill, arrow, i);
	fill->list->str = ft_strdup(fill->tmp_str);
}

int	fill_till_quote_closed(char *original_str, t_fill *fill, t_parse *parse, int k)
{
	char	tmp_quote;

	tmp_quote = original_str[fill->start];
	if (fill->current_quote == 0)
		fill->current_quote = tmp_quote;
	else
		if (fill->current_quote == original_str[fill->start])
			fill->current_quote = 0;
	fill->start++;
	while (original_str[fill->start] != tmp_quote)
	{
		if (original_str[fill->start] == '\0')
		{
			printf("ERROR: quote is not closed.\n"); //TODO: error handle.
			parse->first_node = NULL;
			return (-1);
		}
		fill->tmp_str[k++] = original_str[fill->start++];
	}
	fill->end_pos_of_dollar_var = k;
	fill->start++;
	return (k);
}

void	fill_str(char *original_str, t_fill *fill, t_parse *parse, t_env *env)
{
	int	k;

	fill->tmp_str = (char *) malloc((fill->i - fill->start + 1) * sizeof(char));
	if (fill->tmp_str == NULL)
		printf("malloc failed\n"); //TODO: error handle
	k = 0;
	while (original_str[fill->start] != ' ' && original_str[fill->start] != '\0' && original_str[fill->start] != '>' && original_str[fill->start] != '<')
	{
		if (original_str[fill->start] == '|')
			break ;
		if (original_str[fill->start] == 34 || original_str[fill->start] == 39)
		{
			k = fill_till_quote_closed(original_str, fill, parse, k);
			if (k == -1)
				return ;
			continue ;
		}
		fill->tmp_str[k++] = original_str[fill->start++];
	}
	fill->tmp_str[k] = '\0';
	if (fill->count != 0)
		fill->list = create_extra_node(fill->list);
	if (is_dollar_exist(fill->tmp_str) == 1 && (fill->current_quote == 0 || fill->current_quote == 34))
		fill->list->str = convert_str_from_dollar(fill->tmp_str, fill->current_quote, fill->end_pos_of_dollar_var, env);
	else
		fill->list->str = ft_strdup(fill->tmp_str);
}
