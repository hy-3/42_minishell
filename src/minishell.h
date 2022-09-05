#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"
# include <sys/uio.h>
# include <stddef.h>
# include <termios.h>

# define BUFFER_SIZE 10 //TODO: check (for gnl)

typedef struct s_list
{
	char			*str;
	struct s_list	*extra;
	struct s_list	*next;
}	t_list;

typedef struct s_env
{
	char	**first_envp;
	char	**current_envp;
	char	*pathenv;
	int		num_of_next_node;
	int		num_of_child;
	int		p[100][2]; //TODO: p[ARG_MAX][2];
	int		status_code; //TODO: implement
}	t_env;

typedef struct s_cmd
{
	char	*exec_args[100]; //TODO: *exec_args[ARG_MAX];
	int		pid;
	int		input_fd;
	int		output_fd;
	int		is_heredoc;
	int		heredoc_p[2];
	int		num_of_args;
	int		is_error;
}	t_cmd;

typedef struct s_parse
{
	t_list	*first_node;
	int		i;
	int		start;
	int		count;
	int		num_of_single_quote;
	int		num_of_double_quote;
	int		is_quote_closed;
	int		pipe_condition;
}	t_parse;

typedef struct s_fill
{
	int		i;
	int		start;
	int		count;
	char	*tmp_str;
	char	current_quote;
	int		end_pos_of_dollar_var;
	t_list	*list;
}	t_fill;

typedef struct s_dollar
{
	int		start;
	int		tmp_start;
	int		end;
	char	*str_dollar_part;
	int		size_dollar_part;
}	t_dollar;

// src/parse
//	- parse.c
t_list	*parse(char *original_str, t_env *env);
//	- check.c
void	check_pipe_condition(char *original_str, t_parse *parse);
void	check_quote_condition(t_parse *parse, char c);
int		is_include_cmd(char *original_str, t_fill *fill);
//	- fill_str.c
void	fill_str(char *original_str, t_fill *fill, t_parse *parse, t_env *env);
void	fill_str_allows(char *original_str, t_fill *fill, t_parse *parse);
//	- dollar.c
int		is_dollar_exist(char *tmp_str);
char	*convert_str_from_dollar(t_fill *fill, t_env *env);

// src/env
//	- env_upd.c
char	**copy_env(char **old_envp);
char	**upd_to_new_env(t_env *env, t_cmd *cmd);
char	**create_new_env_with_str(char **old_envp, char *str);
//	- env_util.c
char	*get_value_of_pathenv(char **envp);
int		calc_envp_size(char **envp);
int		count_till_equal(char *str);
int		is_exist_in_env(char **envp, char *str);
int		is_valid_envname(char *str);

// src/cmd
//	- pipex.c
void	pipex(t_list *list, t_env *env);
//	- check_cmd.c
char	*is_cmd_exist_and_executable(char *path_env, char *cmd);
//	- external_cmd.c
void	exec_external_cmd(t_cmd *cmd, t_env *env, int i);

// src/cmd/builtin
//	- *.c
void	exec_cd(t_cmd *cmd, t_env *env, int i);
void	exec_echo(t_cmd *cmd, t_env *env, int i);
void	exec_env(t_cmd *cmd, t_env *env, int i);
void	exec_export(t_cmd *cmd, t_env *env, int i);
void	exec_pwd(t_cmd *cmd, t_env *env, int i);
void	exec_unset(t_cmd *cmd, t_env *env, int i);

// redirection
//	- check_arrows.c
t_list	*check_arrows(t_list *list, t_cmd *cmd, t_env *env);
//	- bultin_fd.c
int		get_output_fd(t_cmd *cmd, t_env *env, int i);
//	- external_cmd_fd.c
void	organize_fd(t_cmd *cmd, t_env *env, int i);

// src/util
//	- list.c
int		count_next_node(t_list *list);
t_list	*create_next_node(t_list *list, int count);
t_list	*create_extra_node(t_list *list);
int		is_nullstr_in_list(t_list *list);
//	- split_to_str.c
char	**split_to_str(char const *s, char c);
int		count_num_of_str(char const *s, char c);
void	cust_free(char **res);
//	- stderr.c
void	cust_perror(char *str, int status);
void	cust_write(char *str, int status);

// lib/get_next_line
//	- get_next_line.c
char	*get_next_line(int fd);

#endif