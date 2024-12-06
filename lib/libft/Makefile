NAME = libft.a

GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
RESET = \033[0m

CC = gcc -c

FLAGS = -Wall -Wextra -Werror

AR = ar -rcs

SRCS = ft_atoi.c \
		ft_ato_long.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_free_array_str.c \
		ft_free_ptr.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_isspace.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strcmp.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_realloc.c \
		get_next_line.c \

OBJ_FILES = $(patsubst %.c, %.o, $(SRCS))
OBJ = $(addprefix ./, $(OBJ_FILES))

all: $(NAME)

$(NAME):
	@echo "$(BLUE)(just) a minute ⌛...$(RESET)"
	$(CC) $(FLAGS) $(SRCS)
	$(AR) $(NAME) $(OBJ)
	ranlib $(NAME)
	@echo "\n$(NAME): $(GREEN)$(NAME) was created ✓$(RESET)"
	@echo


clean:
	@echo "\n$(NAME): $(RED)object (*.o) files were deleted ✗$(RESET)"
	/bin/rm -f $(OBJ)
	@echo

fclean: clean
	@echo "$(NAME): $(RED)$(NAME) was deleted ✗$(RESET)"
	/bin/rm -rf $(NAME)
	@echo

re: fclean all

.PHONY: all clean fclean re
