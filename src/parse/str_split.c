#include "../minishell.h"

t_imput	*cust_split(char const *s, char c)
{
	int		i;
	int		k;
	int		start;
	t_imput	*parsed_imput;
	t_imput	*first_parsed_imput;
	int		num_of_quote;
	char 	tmp_quote;
	int		count;

	// if (s == NULL)
		//TODO: error handle
	i = 0;
	count = 0;
	parsed_imput = (t_imput *) malloc(sizeof(t_imput));
	// if (parsed_imput == NULL)
		//TODO: error handle
	parsed_imput->str = NULL;
	parsed_imput->next = NULL;
	first_parsed_imput = parsed_imput;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count++;
			if (count > 1)
			{
				parsed_imput->next = (t_imput *) malloc(sizeof(t_imput));
				// if (parsed_imput->next == NULL)
					//TODO: error handle
				parsed_imput = parsed_imput->next;
			}
			start = i;
			num_of_quote = 0;
			while ((num_of_quote > 0 && s[i] != '\0') || (s[i] != c && s[i] != '\0'))
			{
				if (s[i] == 34 || s[i] == 39)
					num_of_quote++;
				if (s[i] == '|')
				{
					if (start == i)
						i++;
					break ;
				}
				i++;
			}
			parsed_imput->str = (char *) malloc((i - start + 1) * sizeof(char));
			// if (parsed_imput->str == NULL)
				//TODO: error handle
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
						parsed_imput->str[k++] = s[start];
					}
					start++;
					continue;
				}
				parsed_imput->str[k++] = s[start++];
			}
			parsed_imput->str[k] = '\0';
			parsed_imput->next = NULL;
		}
		else
			i++;
	}
	return (first_parsed_imput);
}
