#include "../../minishell.h"

void	upd_env_value(char **new_envp, char *str_old_envp, char *pos_equal, int k)
{
	int		l;
	int		index_equal_pos;
	char	*tmp_str;

	l = 0;
	index_equal_pos = count_till_equal(str_old_envp);
	tmp_str = (char *) malloc((index_equal_pos + 1) * sizeof(char));
	if (tmp_str == NULL)
		cust_write("malloc failed\n", 1);
	while (l < index_equal_pos)
	{
		tmp_str[l] = str_old_envp[l];
		l++;
	}
	tmp_str[l] = '\0';
	new_envp[k] = ft_strjoin(tmp_str, pos_equal);
	free(tmp_str);
}

char	**create_newenv_upd(char **old_envp, char *str)
{
	char	*pos_equal;
	char	**new_envp;
	int		i;
	int		k;

	i = 0;
	k = 0;
	pos_equal = ft_strchr(str, '=');
	if (pos_equal != NULL)
	{
		new_envp = (char **) malloc((calc_envp_size(old_envp)) * sizeof(char *));
		if (new_envp == NULL)
			cust_write("malloc failed\n", 1);
		while (old_envp[i] != NULL)
		{
			if (ft_strncmp(old_envp[i], str, count_till_equal(str)) == 0)
			{
				if (ft_strchr(old_envp[i], '=') != NULL)
					upd_env_value(new_envp, old_envp[i], pos_equal, k++);
				else
					new_envp[k++] = ft_strjoin(old_envp[i], pos_equal);
			}
			else
				new_envp[k++] = ft_strdup(old_envp[i]);
			free(old_envp[i++]);
		}
		new_envp[k] = NULL;
		return (new_envp);
	}
	return (NULL);
}

char	**create_newenv_add(char **old_envp, char *str)
{
	char	**new_envp;
	int		i;
	int		k;

	new_envp = (char **) malloc((calc_envp_size(old_envp) + 1) * sizeof(char *));
	if (new_envp == NULL)
		cust_write("malloc failed\n", 1);
	i = 0;
	k = 0;
	while (old_envp[i] != NULL)
	{
		new_envp[k++] = ft_strdup(old_envp[i]);
		free(old_envp[i++]);
	}
	new_envp[k++] = ft_strdup(str);
	new_envp[k] = NULL;
	return (new_envp);
}

char	**handle_export(char **old_envp, char *str, t_env *env)
{
	char	**new_envp;

	if (is_valid_envname(str) == 0)
	{
		printf("export: `%s': not a valid identifier\n", str);
		env->status_code = 1;
		return (old_envp);
	}
	if (is_exist_in_env(old_envp, str) == 0)
		return (create_newenv_add(old_envp, str));
	new_envp = create_newenv_upd(old_envp, str);
	if (new_envp != NULL)
		return (new_envp);
	return (old_envp);
}

void	cmd_export(t_cmd *cmd, t_env *env, int fd)
{
	int		k;
	char	*new_str;

	k = 0;
	while (env->current_envp[k] != NULL)
	{
		new_str = ft_strjoin("declare -x ", env->current_envp[k]);
		write(fd, new_str, ft_strlen(new_str));
		write(fd, "\n", 1);
		free(new_str);
		k++;
	}
}

void	exec_export(t_cmd *cmd, t_env *env, int i)
{
	int	k;

	if (cmd->num_of_args == 1)
		cmd_export(cmd, env, get_output_fd(cmd, env, i));
	else
	{
		k = 1;
		while (cmd->exec_args[k] != NULL)
			env->current_envp = handle_export(env->current_envp, cmd->exec_args[k++], env);
	}
}
