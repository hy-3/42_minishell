#include "../minishell.h"

int	is_dollar_exist(char *tmp_str)
{
	int	i;

	i = 0;
	while(tmp_str[i] != '\0')
	{
		if (tmp_str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*convert_str_from_dollar(char *tmp_str)
{
	int		i;
	int		k;
	int		start_dollar;
	int		tmp_start_dollar;
	int		end_dollar;
	char	*dollar_part;
	char	*str_dollar_part;
	int		total_length;
	char	*converted_str;
	int		size_dollar_part;

	i = 0;
	while (tmp_str[i] != '$')
		i++;
	start_dollar = i;
	tmp_start_dollar = start_dollar;
	while (tmp_str[i] != '\0' && tmp_str[i] != 39 && tmp_str[i] != 34)
		i++;
	end_dollar = i;
	dollar_part = (char *) malloc((end_dollar - start_dollar) * sizeof(char));
	k = 0;
	while (start_dollar < (end_dollar - 1))
	{
		dollar_part[k] = tmp_str[++start_dollar];
		k++;
	}
	dollar_part[k] = '\0';
	str_dollar_part = getenv(dollar_part);
	free(dollar_part);

	if (str_dollar_part == NULL)
		size_dollar_part = 0;
	else
		size_dollar_part = ft_strlen(str_dollar_part);
	total_length = tmp_start_dollar + size_dollar_part + (ft_strlen(tmp_str) - end_dollar) + 1;
	converted_str = (char *) malloc(total_length * sizeof(char));

	i = 0;
	while (i < tmp_start_dollar)
	{
		converted_str[i] = tmp_str[i];
		i++;
	}
	k = 0;
	while (k < size_dollar_part)
		converted_str[i++] = str_dollar_part[k++];
	while (tmp_str[end_dollar] != '\0')
		converted_str[i++] = tmp_str[end_dollar++];
	converted_str[i] = '\0';
	return (converted_str);
}
