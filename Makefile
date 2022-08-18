NAME = minishell
CC = gcc
# FLAG_WARN = -Wall -Wextra -Werror
FLAG_LIB = -lreadline
LIBFT_PATH = lib/libft/
LIBFT = lib/libft/libft.a
SRC = src/main.c \
	  src/parse.c \
	  src/cmd/split_to_str.c \
	  src/cmd/stderr.c \
	  src/cmd/pipex.c \
	  src/cmd/check_cmd.c \
	  src/cmd/list.c

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