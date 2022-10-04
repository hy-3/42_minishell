/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:47:38 by enevado           #+#    #+#             */
/*   Updated: 2022/10/04 17:16:14 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s1len;

	if (!s1)
		return (NULL);
	while (ft_strchr(set, *s1) && *s1 != '\0')
		s1++;
	s1len = ft_strlen(s1);
	if (!*s1)
		return (ft_strdup(""));
	while (ft_strchr(set, s1[s1len]) && s1len > 0)
		s1len--;
	return (ft_substr(s1, 0, s1len + 1));
}
