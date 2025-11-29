GRAY := \033[0;90m
RED := \033[0;91m
GREEN := \033[0;92m
YELLOW := \033[0;93m
BLUE := \033[0;94m
MAGENTA := \033[0;95m
CYAN := \033[0;96m
RESET := \033[0;39m

NAME := cub3D

SRC_DIR := src
OBJ_DIR := obj

SRC :=	$(SRC_DIR)/main.c \
		$(SRC_DIR)/render.c


OBJ := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRC:.c=.o))
INCLUDE := inc

LIBFT := my_libft/libft/libft.a
FT_PRINTF := my_libft/ft_printf/ft_printf.a
GNL := my_libft/gnl/gnl.a
MINILIBX := minilibx-linux/libmlx_Linux.a

CC := cc
CFLAGS := -Wall -Wextra -Werror -g3 -I$(INCLUDE) #-O3 

RM := rm -rf

#Name has to be the first one to be checked and executed
$(NAME): $(OBJ) $(LIBFT) $(FT_PRINTF) $(GNL) $(MINILIBX)
		@$(CC) $(CFLAGS) $^ -I$(INCLUDE) -Imlx_linux -O3 -Lmlx -lm -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
		@echo "${GREEN} Created $(NAME) ${RESET}"
		
$(OBJ): $(OBJ_DIR)%.o:$(SRC_DIR)%.c
		@mkdir -p $(OBJ_DIR)
		@mkdir -p $(OBJ_DIR)/execution
		@mkdir -p $(OBJ_DIR)/parsing
		@mkdir -p $(OBJ_DIR)/utils
		@$(CC) $(CFLAGS) -c -o $@ $^
		@echo "${CYAN} ~ Compiled -> ${MAGENTA}$< ${RESET}"

$(LIBFT):
		@make -C my_libft/libft
		
$(FT_PRINTF): 
		@make -C my_libft/ft_printf

$(GNL):
		@make -C my_libft/gnl

$(MINILIBX):
		@make -C minilibx-linux

#all must always be the first rule!
all: $(NAME)

v: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes  -s ./cub3D
clean:
		@make clean -C my_libft/libft
		@make clean -C my_libft/ft_printf
		@make clean -C my_libft/gnl
		@make clean -C minilibx-linux
		@$(RM) $(OBJ) $(OBJ_DIR)
		@echo "${RED} Cleaned $(OBJ_DIR) directory ${RESET}"

fclean: clean
		@make fclean -C my_libft/libft
		@make fclean -C my_libft/ft_printf
		@make fclean -C my_libft/gnl
		@make clean -C minilibx-linux
		@$(RM) $(NAME)
		@echo "${RED} Cleaned $(NAME) library ${RESET}"

re: fclean all

.PHONY: all clean fclean re 
