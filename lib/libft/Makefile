CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = libft.a

PART1_SRC = \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c
PART2_SRC = \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c
MANDATORY_SRC = $(PART1_SRC) $(PART2_SRC)
MANDATORY_OBJ = $(MANDATORY_SRC:%.c=%.o)

BONUS_SRC = \
	ft_lstnew_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstsize_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstmap_bonus.c
BONUS_OBJ = $(BONUS_SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(MANDATORY_OBJ)
	@ar -rcs $(NAME) $(MANDATORY_OBJ)

bonus: .bonus

.bonus: $(MANDATORY_OBJ) $(BONUS_OBJ)
	@touch .bonus
	@ar -rcs $(NAME) $(MANDATORY_OBJ) $(BONUS_OBJ)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

re: fclean all

fclean: clean
	@echo "Deleting $(NAME)"
	@rm -f $(NAME)

clean:
	@echo "Deleting object files"
	@rm -f $(MANDATORY_OBJ) $(BONUS_OBJ)
	@rm -f .bonus

.PONHY: all bonus re fclean clean
