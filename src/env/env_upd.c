#include "../minishell.h"

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

char	**create_new_env_with_str(char **old_envp, char *str, t_env *env)
{
	char	**new_envp;
	int		k;
	int		l;

	if (is_valid_envname(str) == 0)
	{
		printf("export: `%s': not a valid identifier\n", str);
		env->status_code = 1;
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

char	**upd_to_new_env(t_env *env, t_cmd *cmd)
{
	char	**new_envp;
	int		i;

	i = 1;
	while (cmd->exec_args[i] != NULL)
	{
		if (i == 1)
			new_envp = create_new_env_without_str(env->current_envp, cmd->exec_args[i]);
		else
			new_envp = create_new_env_without_str(new_envp, cmd->exec_args[i]);
		i++;
	}
	return (new_envp);
}
