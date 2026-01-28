# **************************************************************************** #
#                                CUB3D MAKEFILE                                 #
# **************************************************************************** #

# Compiler and flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -fsanitize=address -g3 -O0 

# Project name
NAME        = cub3D

# Directories
SRC_DIR     = src
INC_DIR     = include

LIBFT_DIR   = $(INC_DIR)/libft
MLX_DIR     = $(INC_DIR)/minilibx-linux

# Libraries
LIBFT_A     = $(LIBFT_DIR)/libft.a
LIBFT_LIB   = -L$(LIBFT_DIR) -lft

MLX_LIB     = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# Source files
SRCS        = $(shell find $(SRC_DIR) -name "*.c")
OBJS        = $(SRCS:.c=.o)

# ----------------------------------------------------------------------------- #
# Default target
# ----------------------------------------------------------------------------- #

all: submodules mlx libft $(NAME)

# ----------------------------------------------------------------------------- #
# Git submodules
# ----------------------------------------------------------------------------- #

submodules:
	@echo "Updating submodules..."
	@git submodule update --init --recursive

# ----------------------------------------------------------------------------- #
# Libraries
# ----------------------------------------------------------------------------- #

libft: $(LIBFT_A)

$(LIBFT_A):
	@echo "Compiling Libft..."
	@make -C $(LIBFT_DIR)

mlx:
	@echo "Compiling MiniLibX..."
	@make -C $(MLX_DIR)

# ----------------------------------------------------------------------------- #
# Build
# ----------------------------------------------------------------------------- #

$(NAME): $(OBJS)
	@echo "Building $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) \
		-I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) \
		$(LIBFT_LIB) $(MLX_LIB) -o $(NAME)

# Object files
%.o: %.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -c $< -o $@

# ----------------------------------------------------------------------------- #
# Cleaning rules
# ----------------------------------------------------------------------------- #

clean:
	@echo "Cleaning object files..."
	rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean

fclean: clean
	@echo "Removing executable and libraries..."
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(MLX_DIR) clean

re: fclean all

# ----------------------------------------------------------------------------- #
# Run
# ----------------------------------------------------------------------------- #

run: all
	./$(NAME) assets/maps/map.cub

.PHONY: all clean fclean re run submodules mlx libft
