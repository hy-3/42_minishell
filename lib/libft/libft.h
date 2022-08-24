/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvd <nvd@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 13:46:20 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/08/24 17:58:21 by nvd              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
#define LIBFT_H

#include <stddef.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFER_SIZE 1

typedef struct s_glist
{
    char *c;
    struct s_glist *next;
} t_glist;

char *get_next_line(int fd);

char *ft_strchr(const char *s, int c);
char *ft_strdup(const char *s1);
char *ft_strjoin(char const *s1, char const *s2);
size_t ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t ft_strlen(const char *str);
int ft_strncmp(const char *s1, const char *s2, size_t n);
char *ft_strnstr(const char *haystack, const char *needle, size_t len);
char *ft_strtrim(char const *s1, char const *set);
char *ft_strrchr(const char *s, int c);
void ft_putstr_fd(char *s, int fd);
#endif
