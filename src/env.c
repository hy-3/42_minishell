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

void	copy_env_without_param(t_env_param *env_p, t_cmd_param *cmd_p, int num_node_ver)
{
	char	**new_envp;
	char	**old_envp;
	char	**tmp_envp;
	int		i;
	int		k;
	int		l;

	i = 1;
	while (cmd_p->exec_args[i] != NULL)
	{
		new_envp = (char **) malloc(calc_envp_size(env_p->envp) * sizeof(char *));
		if (i == 1)
			old_envp = env_p->envp;
		else
			old_envp = tmp_envp;
		k = 0;
		l = 0;
		while (old_envp[k] != NULL)
		{
			if (count_till_equal(old_envp[k]) == count_till_equal(cmd_p->exec_args[i]))
			{
				if (ft_strncmp(old_envp[k], cmd_p->exec_args[i], count_till_equal(cmd_p->exec_args[i])) == 0)
				{
					free(old_envp[k]);
					k++;
				}
				else
				{
					new_envp[l] = ft_strdup(old_envp[k]);
					free(old_envp[k]);
					k++;
					l++;
				}
			}
			else
			{
				new_envp[l] = ft_strdup(old_envp[k]);
				free(old_envp[k]);
				k++;
				l++;
			}
		}
		new_envp[l] = NULL;
		tmp_envp = new_envp;
		i++;
	}
	env_p->envp = new_envp;
}
