#include "../minishell.h"

void	fill_string(char const *s, char c, t_imput *parsed_imput)
{
	int		i;
	int		k;
	int		l;
	int		start;
	t_imput	*current;
	int		num_of_double_quote;
	int		num_of_single_quote;

	i = 0;
	current = parsed_imput;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			start = i;
			num_of_double_quote = 0;
			num_of_single_quote = 0;
			while ((num_of_double_quote == 1 && s[i] != '\0') || (num_of_single_quote == 1 && s[i] != '\0') || (s[i] != c && s[i] != '\0'))
			{
				if (s[i] == 34)
					num_of_double_quote++;
				if (s[i] == 39)
					num_of_single_quote++;
				i++;
			}
			current->str = (char *) malloc((i - start + 1) * sizeof(char));
			// if (current->str == NULL)
			// 	free
			l = 0;
			while ((i - start) > 0)
			{
				if (s[start] == 34 || s[start] == 39)
				{
					start++;
					continue;
				}
				current->str[l++] = s[start++];
			}
			current->str[l] = '\0';
			current->next = (t_imput *) malloc(sizeof(t_imput));
			// if (current->next == NULL)
				// free
			current = current->next;
		}
		else
			i++;
	}
	current = NULL;
}

void	cust_split(char const *s, char c, t_imput *parsed_imput)
{
	// if (s == NULL)
	fill_string(s, c, parsed_imput);
}
