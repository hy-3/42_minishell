#include "../minishell.h"

int	is_include_cmd(char *original_str, t_fill *fill)
{
	while (original_str[fill->start] == ' ')
		fill->start++;
	if (original_str[fill->start] == '|' || original_str[fill->start] == '\0')
		return (0);
	return (1);
}

void	check_quote_condition(t_parse_param *parse_p, char c)
{
	if (c == 39)
		parse_p->num_of_single_quote++;
	if (c == 34)
		parse_p->num_of_double_quote++;
	if (parse_p->num_of_single_quote % 2 == 0 && parse_p->num_of_double_quote % 2 == 0)
		parse_p->is_quote_closed = 1;
	else
		parse_p->is_quote_closed = 0;
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

void	check_pipe_condition(char *original_str, t_parse_param *parse_p)
{
	int	num_of_pipe;

	num_of_pipe = 0;
	if (parse_p->i == 0)
	{
		printf("parse error near `|'\n"); //TODO: error handle
		parse_p->first_node = NULL;
		parse_p->pipe_condition = 2;
		return ;
	}
	num_of_pipe = check_pipe_num(original_str, parse_p->i + 1);
	if (num_of_pipe > 2)
	{
		printf("syntax error near unexpected token `|' (pipe continued)\n"); //TODO: error handle
		parse_p->first_node = NULL;
		parse_p->pipe_condition = 2;
	}
	if (num_of_pipe == 2)
		parse_p->pipe_condition = 1;
	return ;
}
