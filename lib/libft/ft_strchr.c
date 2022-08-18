/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:38:20 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/16 19:31:20 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Find first occurence of [c] from [s].
 * 
 * @param s(const char *): Source string to be looked for.
 * @param c(int): Char that it will look for.
 * @return (char *): Pointer to [c] or NULL if [c] doesn't appear.
 */
char	*ft_strchr(const char *s, int c)
{
	char	*new_s;
	int		i;

	if (s == NULL)
		return (NULL);
	new_s = (char *) s;
	i = 0;
	while (new_s[i] != '\0')
	{
		if (new_s[i] == (char) c)
			return (&new_s[i]);
		i++;
	}
	if (c == 0)
		return (&new_s[i]);
	else
		return (NULL);
}
