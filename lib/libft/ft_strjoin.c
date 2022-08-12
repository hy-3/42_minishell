/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:38:40 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/15 20:45:11 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Return new string which concatenate [s1] and [s2].
 * 
 * @param s1(char const *): Prifix string.
 * @param s2(char const *): Suffix string.
 * @return (char *): New string ([s1] + [s2]).
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	total_len;
	unsigned int	i;
	unsigned int	k;
	char			*res;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc((total_len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	k = 0;
	i = 0;
	while (s1[i] > 0)
		res[k++] = s1[i++];
	i = 0;
	while (s2[i] > 0)
		res[k++] = s2[i++];
	res[k] = '\0';
	return (res);
}
