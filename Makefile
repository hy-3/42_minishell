NAME = minishell
CC = gcc
# FLAG_WARN = -Wall -Wextra -Werror
FLAG_LIB = -lreadline
LIBFT_PATH = lib/libft/
LIBFT = lib/libft/libft.a
SRC = src/main.c \
	  src/parse/parse.c \
	  src/parse/check.c \
	  src/parse/fill_str.c \
	  src/cmd/check_cmd.c \
	  src/cmd/external_cmd.c \
	  src/cmd/pipex.c \
	  src/cmd/builtin/cd.c \
	  src/cmd/builtin/echo.c \
	  src/cmd/builtin/env.c \
	  src/cmd/builtin/export.c \
	  src/cmd/builtin/pwd.c \
	  src/cmd/builtin/unset.c \
	  src/env/env.c \
	  src/env/dollar.c \
	  src/redirection/redirect.c \
	  src/redirection/builtin_output_fd.c \
	  src/redirection/external_cmd_inoutput_fd.c \
	  src/util/list.c \
	  src/util/split_to_str.c \
	  src/util/stderr.c \
	  lib/get_next_line/get_next_line.c \
	  lib/get_next_line/get_next_line_utils.c

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFT_PATH)
	$(CC) $(OBJ) $(LIBFT) $(FLAG_LIB) $(FLAG_WARN) -fsanitize=address -g3 -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT_PATH)
	rm -f $(OBJ)

fclean: clean
	make clean
	rm -f $(LIBFT)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re