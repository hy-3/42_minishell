/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:39:09 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/15 20:12:54 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_len_of_str(char const *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i++] != '\0')
		count++;
	return (count);
}

/**
 * @brief Apply function[f] to each character of given string[s] 
 *        & return a new string.
 *
 * @param s(char const *): Source string.
 * @param f(char *(unsigned int, char)): Pointer to function to apply to char.
 * @return (char *): New string after function[f] applied.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len_of_s;
	int		i;
	char	*res;

	if (s == NULL)
		return (NULL);
	len_of_s = count_len_of_str(s);
	res = (char *) malloc((len_of_s + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		res[i] = f(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
