#include "minishell.h"

int	calc_envp_size(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	return (i + 1);
}

char	**copy_env(char **old_envp)
{
	int		i;
	char	**new_envp;

	i = 0;
	new_envp = (char **) malloc(calc_envp_size(old_envp) * sizeof(char *));
	while (old_envp[i] != NULL)
	{
		new_envp[i] = ft_strdup(old_envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
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
	if (ft_isdigit(str[0]) == 1)
		return (0);
	return (1);
}

char	**create_new_env_with_str(char **old_envp, char *str)
{
	char	**new_envp;
	int		k;
	int		l;

	if (is_valid_envname(str) == 0)
	{
		printf("export: %s:not a valid identifier\n", str); //TODO: error handle
		return (old_envp);
	}
	if (is_exist_in_env(old_envp, str) == 0)
	{
		new_envp = (char **) malloc((calc_envp_size(old_envp) + 1) * sizeof(char *));
		k = 0;
		l = 0;
		while (old_envp[k] != NULL)
		{
			new_envp[l++] = ft_strdup(old_envp[k]);
			free(old_envp[k++]);
		}
		new_envp[l++] = ft_strdup(str);
		new_envp[l] = NULL;
		return (new_envp);
	}
	return (old_envp);
}

char	**create_new_env_without_str(char **old_envp, char *str)
{
	char	**new_envp;
	int		k;
	int		l;

	new_envp = (char **) malloc(calc_envp_size(old_envp) * sizeof(char *));
	k = 0;
	l = 0;
	while (old_envp[k] != NULL)
	{
		if (count_till_equal(old_envp[k]) == count_till_equal(str))
		{
			if (ft_strncmp(old_envp[k], str, count_till_equal(str)) == 0)
			{
				free(old_envp[k++]);
				continue ;
			}
		}
		new_envp[l++] = ft_strdup(old_envp[k]);
		free(old_envp[k++]);
	}
	new_envp[l] = NULL;
	return (new_envp);
}

char	**upd_to_new_env(t_env_param *env_p, t_cmd_param *cmd_p)
{
	char	**new_envp;
	char	**old_envp;
	int		i;

	i = 1;
	while (cmd_p->exec_args[i] != NULL)
	{
		if (i == 1)
			new_envp = create_new_env_without_str(env_p->envp, cmd_p->exec_args[i]);
		else
			new_envp = create_new_env_without_str(new_envp, cmd_p->exec_args[i]);
		i++;
	}
	return (new_envp);
}
