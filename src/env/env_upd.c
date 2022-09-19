/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_upd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:03:43 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/09/19 18:55:48 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**copy_env(char **old_envp)
{
	int		i;
	char	**new_envp;

	i = 0;
	new_envp = (char **) malloc(calc_envp_size(old_envp) * sizeof(char *));
	if (new_envp == NULL)
		cust_write("malloc failed\n", 1);
	while (old_envp[i] != NULL)
	{
		new_envp[i] = ft_strdup(old_envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

void	upd_env_value(char **new_envp, char *str, char *pos_equal, int k)
{
	int		l;
	int		index_equal_pos;
	char	*tmp_str;

	l = 0;
	index_equal_pos = count_till_equal(str);
	tmp_str = (char *) malloc((index_equal_pos + 1) * sizeof(char));
	if (tmp_str == NULL)
		cust_write("malloc failed\n", 1);
	while (l < index_equal_pos)
	{
		tmp_str[l] = str[l];
		l++;
	}
	tmp_str[l] = '\0';
	new_envp[k] = ft_strjoin(tmp_str, pos_equal);
	free(tmp_str);
}

void	upd_envp(char **old_envp, char **new_envp, char *str, char *pos_equal)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
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
	free(old_envp);
	new_envp[k] = NULL;
}

char	**create_newenv_upd(char **old_envp, char *str, char *pos_equal)
{
	char	**new_envp;

	if (pos_equal != NULL)
	{
		new_envp = (char **) malloc((calc_envp_size(old_envp)) \
						* sizeof(char *));
		if (new_envp == NULL)
			cust_write("malloc failed\n", 1);
		upd_envp(old_envp, new_envp, str, pos_equal);
		return (new_envp);
	}
	return (NULL);
}

char	**create_newenv_add(char **old_envp, char *str)
{
	char	**new_envp;
	int		i;
	int		k;

	new_envp = (char **) malloc((calc_envp_size(old_envp) + 1) \
					* sizeof(char *));
	if (new_envp == NULL)
		cust_write("malloc failed\n", 1);
	i = 0;
	k = 0;
	while (old_envp[i] != NULL)
	{
		new_envp[k++] = ft_strdup(old_envp[i]);
		free(old_envp[i++]);
	}
	free(old_envp);
	new_envp[k++] = ft_strdup(str);
	new_envp[k] = NULL;
	return (new_envp);
}
