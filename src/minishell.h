#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
}	t_list;

typedef struct s_env_param
{
	char	**envp;
	char	*pathenv;
}	t_env_param;

typedef struct s_cmd_param
{
	char	*exec_args[100]; //TODO: *exec_args[ARG_MAX];
	char	**cmd_with_option;
	int		n;
	int		pid;
	int		status; //TODO: implement
}	t_cmd_param;

//	src/parse.c
t_list	*parse(char *original_str);
//	src/cmd/pipex.c
int		pipex(t_list *list, char *envp[], int list_size);
//	src/cmd/check_cmd.c
char	*get_value_of_pathenv(char **envp);
char	*is_cmd_exist_and_executable(char *path_env, char *cmd);
//	src/cmd/list.c
void	list_iter(t_list *list, t_env_param *env_p, int list_size, void (*f)(char *str, t_env_param *env_p, int i, int list_size));
//	src/cmd/stderr.c
void	cust_perror(char *str, int status);
void	cust_write(char *str, int status);
//	src/cmd/split_to_str.c
char	**split_to_str(char const *s, char c);
int		count_num_of_str(char const *s, char c);
void	cust_free(char **res);

//	Libft
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *str);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

#endif