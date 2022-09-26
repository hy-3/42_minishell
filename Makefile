NAME = minishell
CC = gcc
FLAG_WARN = -Wall -Wextra -Werror #-fsanitize=address -g3
# LDFLAGS = -L ~/brew/opt/readline/lib/
# CPPFLAGS = -I ~/brew/opt/readline/include/
LDFLAGS = -L /usr/local/opt/readline/lib
CPPFLAGS = -I /usr/local/opt/readline/include
FLAG_LIB = -lreadline $(LDFLAGS) $(CPPFLAGS)
LIBFT_PATH = lib/libft/
LIBFT = $(LIBFT_PATH)/libft.a
SRC = src/main.c \
	  src/parse/parse.c \
	  src/parse/check.c \
	  src/parse/fill_str.c \
	  src/parse/dollar.c \
	  src/parse/dollar_util.c \
	  src/cmd/check_cmd.c \
	  src/cmd/external_cmd.c \
	  src/cmd/pipex.c \
	  src/cmd/close_pipe.c \
	  src/cmd/wait.c \
	  src/cmd/builtin/cd.c \
	  src/cmd/builtin/echo.c \
	  src/cmd/builtin/env.c \
	  src/cmd/builtin/exit.c \
	  src/cmd/builtin/export.c \
	  src/cmd/builtin/pwd.c \
	  src/cmd/builtin/unset.c \
	  src/cmd/builtin/history.c \
	  src/env/env_upd.c \
	  src/env/env_util.c \
	  src/env/shlvl.c \
	  src/redirection/check_arrows.c \
	  src/redirection/check_arrows_util.c \
	  src/redirection/builtin_fd.c \
	  src/redirection/external_cmd_fd.c \
	  src/signal/signal.c \
	  src/util/list.c \
	  src/util/string.c \
	  src/util/stderr.c \
	  lib/get_next_line/get_next_line.c \
	  lib/get_next_line/get_next_line_utils.c

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFT_PATH)
	$(CC) $(OBJ) $(LIBFT) $(FLAG_LIB) $(FLAG_WARN) -o $(NAME)

%.o: %.c
	$(CC) $(FLAG_WARN) -c $< -o $@ 

clean:
	make clean -C $(LIBFT_PATH)
	rm -f $(OBJ)

fclean: clean
	make clean
	rm -f $(LIBFT)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re