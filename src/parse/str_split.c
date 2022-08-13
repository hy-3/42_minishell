#include "../minishell.h"

int		strlen_ignore_char(const char *str, char c)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		if (*str != c)
			count++;
		str++;
	}
	return (count);
}

char	*str_trim(char *str, char c)
{
	int		len_of_original;
	int		len_of_new;
	char	*trimmed_str;
	int		i;
	int		k;

	len_of_original = ft_strlen(str);
	len_of_new = strlen_ignore_char(str, c);
	trimmed_str = (char *) malloc(len_of_new * sizeof(char));
	i = 0;
	k = 0;
	while (len_of_original--)
	{
		if (str[i] != c)
		{
			trimmed_str[k] = str[i];
			k++;
		}
		i++;
	}
	return (trimmed_str);
}

//TODO: Add new line
//TODO: if you put double quote and also put odd single quote during [dquote], it shift to [quote]
void	fill_string(char const *s, char c, t_imput *parsed_imput)
{
	int		i;
	int		k;
	int		l;
	int		start;
	t_imput	*current;
	int		num_of_double_quote;
	int		pos_double_quote;
	int		num_of_single_quote;
	int		pos_single_quote;
	char 	*prompt;
	char	*extra_imput;

	i = 0;
	current = parsed_imput;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			start = i;
			num_of_double_quote = 0;
			num_of_single_quote = 0;
			pos_double_quote = -1;
			pos_single_quote = -1;
			while ((num_of_double_quote == 1 && s[i] != '\0') || (num_of_single_quote == 1 && s[i] != '\0') || (s[i] != c && s[i] != '\0'))
			{
				if (s[i] == 34)
				{
					num_of_double_quote++;
					if (num_of_double_quote == 1)
						pos_double_quote = i;
				}
				if (s[i] == 39)
				{
					num_of_single_quote++;
					if (num_of_single_quote == 1)
						pos_single_quote = i;
				}
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
			if (num_of_double_quote / 2 != 0 || num_of_single_quote / 2 != 0)
			{
				if ((pos_single_quote == -1 && pos_double_quote != -1) || pos_double_quote < pos_single_quote) //TODO: fix condition (ls ''')
				{
					printf("*******\n");
					prompt = "dquote> ";
					current->extra = (t_imput *) malloc(sizeof(t_imput));
					current = current->extra;
					current->str = "\n";
					while (1)
					{
						current->extra = (t_imput *) malloc(sizeof(t_imput));
						current = current->extra;
						extra_imput = readline(prompt);
						current->str = str_trim(extra_imput, 34);
						if (ft_strchr(extra_imput, 34) != NULL)
							break ;
					}
					current->extra = NULL;
				}
				else
				{
					printf("$$$$$$\n");
					prompt = "quote> ";
					current->extra = (t_imput *) malloc(sizeof(t_imput));
					current = current->extra;
					current->str = "\n";
					while (1)
					{
						current->extra = (t_imput *) malloc(sizeof(t_imput));
						current = current->extra;
						extra_imput = readline(prompt);
						current->str = str_trim(extra_imput, 39);
						if (ft_strchr(extra_imput, 39) != NULL)
							break ;
					}
					current->extra = NULL;
				}
			}
			else
				current->extra = NULL;
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
