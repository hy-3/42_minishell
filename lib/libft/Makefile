CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = libft.a

PART1_SRC = \
	ft_strchr.c \
	ft_strdup.c \
	ft_strjoin.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strnstr.c \
	ft_strtrim.c
MANDATORY_SRC = $(PART1_SRC)
MANDATORY_OBJ = $(MANDATORY_SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(MANDATORY_OBJ)
	@ar -rcs $(NAME) $(MANDATORY_OBJ)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

re: fclean all

fclean: clean
	@echo "Deleting $(NAME)"
	@rm -f $(NAME)

clean:
	@echo "Deleting object files"
	@rm -f $(MANDATORY_OBJ)
	@rm -f .bonus

.PONHY: all re fclean clean
