#include "../minishell.h"

t_imput	*cust_lstlast(t_imput *lst)
{
	t_imput	*current_node;
	t_imput	*current_next;

	if (lst == NULL)
		return (NULL);
	current_node = lst;
	current_next = lst->next;
	while (current_next != NULL)
	{
		current_node = current_next;
		current_next = current_next->next;
	}
	return (current_node);
}

void	cust_onelst_addback(t_imput **lst, t_imput *new)
{
	t_imput	*current_node;
	t_imput	*current_next;
	size_t	len_of_str;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current_node = (*lst);
	current_next = (*lst)->next;
	while (current_next != NULL)
	{
		current_node = current_next;
		current_next = current_next->next;
	}
	current_node->next = (t_imput *) malloc(sizeof(t_imput));
	current_node = current_node->next;
	len_of_str = ft_strlen(new->str);
	current_node->str = (char *) malloc((len_of_str + 1) * sizeof(char));
	ft_strlcpy(current_node->str, new->str, len_of_str + 1);
	current_node->next = NULL;
}

int	check_pipe(t_imput *parsed_imput)
{
	t_imput	*lstnode;
	size_t	len_of_str;

	lstnode = cust_lstlast(parsed_imput);
	len_of_str = ft_strlen(lstnode->str);
	if (lstnode->str[len_of_str - 1] == '|')
		return (1);
	else
		return (0);
}

void	check_and_modify(t_imput *parsed_imput)
{
	char	*extra_imput;
	t_imput	*extra_parsed_imput;
	char	*prompt;

	if (check_pipe(parsed_imput) == 1)
	{
		prompt = "pipe> "; //TODO: check if prompt [pipe>] has to be like [pipe pipe>] based on num of | .
		extra_imput = readline(prompt);
		extra_parsed_imput = cust_split(extra_imput, ' ');
		cust_onelst_addback(&parsed_imput, extra_parsed_imput);
		free(extra_imput);
	}
}

t_imput	*parse(char *original_imput)
{
	t_imput *parsed_imput;

	parsed_imput = cust_split(original_imput, ' ');
	check_and_modify(parsed_imput);
	return (parsed_imput);
}
