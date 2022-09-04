#include "../minishell.h"

void	handle_str(char *original_str, t_list *list, t_env_param *env_p, t_parse_param *parse_p)
{
	t_fill	fill;

	fill.i = parse_p->i;
	fill.start = parse_p->start;
	fill.count = 0;
	fill.list = list;
	fill.current_quote = 0;
	fill.end_pos_of_dollar_var = 0;
	fill.tmp_str = NULL;
	while ((fill.i - fill.start) > 0)
	{
		if (is_include_cmd(original_str, &fill) == 0)
			break;
		if (original_str[fill.start] == '>' || original_str[fill.start] == '<')
			fill_str_allows(original_str, &fill, parse_p);
		else
			fill_str(original_str, &fill, parse_p, env_p);
		if (parse_p->first_node == NULL)
			return ;
		free(fill.tmp_str);
		fill.count++;
	}
	parse_p->i++;
	parse_p->start = parse_p->i;
}

void	create_node_with_str(char *original_str, t_env_param *env_p, t_parse_param *parse_p)
{
	t_list	*list;

	while (original_str[parse_p->i] != '\0')
	{
		check_quote_condition(parse_p, original_str[parse_p->i]);
		if (original_str[parse_p->i] == '|' && parse_p->is_quote_closed == 1)
		{
			check_pipe_condition(original_str, parse_p);
			if (parse_p->pipe_condition == 1)
				break ;
			else if (parse_p->pipe_condition == 2)
				return ;
			list = create_next_node(list, parse_p->count);
			if (parse_p->count++ == 0)
				parse_p->first_node = list;
			handle_str(original_str, list, env_p, parse_p);
		}
		else
			parse_p->i++;
	}
	list = create_next_node(list, parse_p->count);
	if (parse_p->count == 0)
		parse_p->first_node = list;
	handle_str(original_str, list, env_p, parse_p);
}

t_list	*parse(char *original_str, t_env_param *env_p)
{
	t_parse_param	parse_p;

	parse_p.first_node = NULL;
	parse_p.i = 0;
	parse_p.start = 0;
	parse_p.count = 0;
	parse_p.num_of_single_quote = 0;
	parse_p.num_of_double_quote = 0;
	parse_p.is_quote_closed = 1;
	parse_p.pipe_condition = 0;
	if (original_str == NULL || original_str[0] == '\0')
		return (NULL);
	create_node_with_str(original_str, env_p, &parse_p);
	if (is_nullstr_in_list(parse_p.first_node) == 1)
		return (NULL);
	return (parse_p.first_node);
}
