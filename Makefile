NAME = cub3d

RESET 	= \033[0m
GREEN 	= \033[0;32m
RED 	= \033[0;31m

PATH_SRC 		= ./src/
PATH_OBJS 		= ./objs/
INC_PATH 		= ./include/
VPATH 			= $(shell find $(PATH_SRC) -type d)

LIBFT_PATH 		= ./lib/libft/
LIBFT 			= $(LIBFT_PATH)/libft.a

MLX_PATH	= ./lib/minilibx-linux/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)

MLXFLAGS 		= -Imlx_linux -lXext -lX11 -lm

CC = cc -g
CFLAGS = -Wall -Wextra -Werror

LEAK = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s

RM			= rm -rf
NO_PRINT	= --no-print-directory

INCLUDE = -I $(INC_PATH) -I $(LIBFT_PATH)

SRCS 	=	main.c parse_img.c \
			game_control.c game_draw.c game_engine.c game_loop.c \
			utils2.c utils.c  valid.c \
			parse_map_partial.c parse_text_wall.c parse.c

OBJS = $(addprefix $(PATH_OBJS), $(SRCS:.c=.o))

all: $(MLX) $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIBFT) $(MLX) $(MLXFLAGS) -o $(NAME)
	@echo "$(GREEN)Build Successful$(RESET)"

$(PATH_OBJS)%.o: %.c
	@mkdir -p $(PATH_OBJS)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_PATH) $(NO_PRINT)

$(MLX):
	make -sC $(MLX_PATH)

clean:
	@echo "$(RED)Cleaning objects...$(RESET)"
	@$(RM) $(PATH_OBJS)
	@make -C $(LIBFT_PATH) clean $(NO_PRINT)
	@make -C $(MLX_PATH) clean $(NO_PRINT)
	@echo "$(GREEN)Done!$(RESET)"

fclean: clean
	@echo  "$(RED)Cleaning all...$(RESET)"
	@$(RM) $(NAME)
	@make -C $(LIBFT_PATH) fclean $(NO_PRINT)
	@echo "$(RED)Cleaning binaries...$(RESET)"
	@echo "$(GREEN)Done!$(RESET)"

re: fclean all

norma:
	norminette $(PATH_SRC) $(LIBFT_PATH) $(INC_PATH)

run:
	./cub3d ./maps/2.cub

valgrind:
	$(LEAK) ./cub3d ./maps/1-simple-map.cub

.PHONY: all run re clean fclean
