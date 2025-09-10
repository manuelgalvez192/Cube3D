MAKEFLAGS += --no-print-directory
# PROYECT
NAME = cub3D
MAP = ./maps/map.cub

# PATHS
LIBFT = ./libft/
LIBFT_LIB = $(LIBFT)libft.a
LIBMLX	:= ./MLX42
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

# COMPILER
CC = cc -g3
ARFLAGS = -rc
CFLAGS = -Wall -Wextra -Werror -Iinc

# Remove command
RM = rm -f

# A list of all .c files in the current directory
SRCS = src/main.c						\
		src/free.c						\
		src/parser.c					\
		src/parse_texture.c				\
		src/parse_map.c					\
		src/check_chars.c				\
		src/colors.c					\
		src/player/player.c				\
		src/player/player_movement.c	\
		src/player/player_utils.c		\
		src/mouse.c						\
		src/mlx/mlx.c					\
		src/mlx/hooks.c					\
		src/render/render.c				\
		src/render/dda.c				\
		src/render/dda_utils.c			\
		src/render/3d/render3d.c		\
		src/render/3d/texture.c			\
		src/render/2d/draw.c			\
		src/render/2d/square.c			\
		src/render/2d/minimap.c			\

OBJS = $(SRCS:.c=.o)

# A list of all .o files of bonus
BNS = $(BONUS:.c=.o)

# The default target - builds the project
all: $(NAME)

# A rule to build the project from the .o files
$(NAME): $(LIBFT_LIB) $(MLX_LIB) libmlx $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME) $(LIBFT_LIB) $(LDFLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

$(LIBFT_LIB):
	@make -C $(LIBFT) -f Makefile

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

# A rule to remove all .o files
clean:
	@$(RM) $(OBJS)
	@make -C $(LIBFT) clean
	@make -C $(LIBMLX)/build clean

# A rule to remove all .o files and the project
fclean: clean
	@$(RM) $(NAME)
	@make -C $(LIBFT) fclean

# A rule to rebuild everything from scratch
re: fclean all

# A rule to run the program
run: all
	./$(NAME) $(MAP)

norm:
	norminette src inc

# A special rule to tell make that these targets aren't files
.PHONY: all fclean re clean run error
