/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:39:56 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/16 17:17:21 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*cust_malloc(unsigned int start, size_t len, size_t len_s, int flag)
{
	char	*res;

	if (flag == 1)
		res = (char *) malloc(1 * sizeof(char));
	else
	{
		if (len_s < len)
			res = (char *) malloc((len_s - start + 1) * sizeof(char));
		else
			res = (char *) malloc((len + 1) * sizeof(char));
	}
	if (res == NULL)
		return (NULL);
	return (res);
}

/**
 * @brief Get substring from [s]. Begin from [start] and max size of [len].
 *
 * @param s(char const *): Source string.
 * @param start(unsigned int): Start position to get substring.
 * @param len(size_t): Max size.
 * @return (char *): Substring. NULL if the allocation fails.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			len_s;
	unsigned int	i;
	char			*res;

	if (s == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	i = 0;
	if (len_s < start)
		res = cust_malloc(start, len, len_s, 1);
	else
	{
		res = cust_malloc(start, len, len_s, 0);
		if (res == NULL)
			return (NULL);
		while (*(s + start) != '\0' && len > 0)
		{
			res[i++] = *(s + start++);
			len--;
		}
	}
	if (res != NULL)
		res[i] = '\0';
	return (res);
}
