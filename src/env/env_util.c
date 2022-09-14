#include "../minishell.h"

char	*get_value_of_pathenv(char **envp)
{
	char	*res;
	int		i;

	res = NULL;
	i = 0;
	while (envp[i])
	{
		res = ft_strnstr(envp[i++], "PATH=", 5);
		if (res != NULL)
		{
			res += 5;
			break ;
		}
	}
	return (res);
}

int	calc_envp_size(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	return (i + 1);
}

int	count_till_equal(char *str)
{
	int	count;

	if (str == NULL)
		return (0);
	count = 0;
	while (str[count] != '\0' && str[count] != '=')
		count++;
	return (count);
}

int	is_exist_in_env(char **envp, char *str)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (count_till_equal(envp[i]) == count_till_equal(str))
			if (ft_strncmp(envp[i], str, count_till_equal(str)) == 0)
				return (1);
		i++;
	}
	return (0);
}

int	is_valid_envname(char *str)
{
	if (ft_isdigit(str[0]) == 1 || str[0] == '=' || str[0] == '/')
		return (0);
	return (1);
}
