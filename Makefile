# **************************************************************************** #
#                               CUB3D MAKEFILE                                 #
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

# Source files (auto-detected)
SRCS        = $(shell find $(SRC_DIR) -name "*.c")
OBJS        = $(SRCS:.c=.o)

# Default target
all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
	@echo "Compiling Libft..."
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	@echo "Building $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) -I$(INC_DIR) -I$(LIBFT_DIR) $(LIBFT_LIB) $(MLX_LIB) -o $(NAME)

# Object files
%.o: %.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -c $< -o $@

# Clean object files
clean:
	@echo "Cleaning object files..."
	rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean

# Full clean
fclean: clean
	@echo "Removing executable and libraries..."
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

# Recompile everything
re: fclean all

# Run Cub3D with a default map
run: all
	./$(NAME) assets/maps/map.cub

.PHONY: all clean fclean re run
