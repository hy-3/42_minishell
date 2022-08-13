#include "../minishell.h"

void	fill_string(char const *s, char c, t_imput *parsed_imput)
{
	int		i;
	int		k;
	int		start;
	t_imput	*current;
	int		num_of_quote;
	char 	tmp_quote;

	i = 0;
	current = parsed_imput;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			start = i;
			num_of_quote = 0;
			while ((num_of_quote > 0 && s[i] != '\0') || (s[i] != c && s[i] != '\0'))
			{
				if (s[i] == 34 || s[i] == 39)
					num_of_quote++;
				i++;
			}
			current->str = (char *) malloc((i - start + 1) * sizeof(char));
			// if (current->str == NULL)
			// 	free
			k = 0;
			while ((i - start) > 0)
			{
				if (s[start] == 34 || s[start] == 39)
				{
					tmp_quote = s[start];
					while (s[++start] != tmp_quote)
					{
						if (s[start] == '\0')
						{
							printf("ERROR: quote is not closed.\n");
							exit(1); //TODO: error handling
						}
						current->str[k++] = s[start];
					}
					start++;
					continue;
				}
				current->str[k++] = s[start++];
			}
			current->str[k] = '\0';
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


//TODO: Fix segmentation fault
/*
$ ./minishell 
minishell> ls "'"'sa'""
0: ls
1: 'sa
minishell> ls "'"'sa'""
0: ls
1: 'sa
Segmentation fault: 11
*/