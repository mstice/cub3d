CYAN := \033[0;96m
MAGENTA := \033[0;95m
YELLOW := \033[0;93m
GREEN := \033[0;92m
RED := \033[0;91m
RESET := \033[0m

NAME := cub3D

INCLUDE := inc
SRC_DIR := src
OBJ_DIR := obj

SRC :=	$(SRC_DIR)/main.c \
		$(SRC_DIR)/parsing/map_reformats.c \
		$(SRC_DIR)/parsing/map_checks.c \
		$(SRC_DIR)/parsing/file_checks.c \
		$(SRC_DIR)/parsing/parsing.c \
		$(SRC_DIR)/execution/draw_scene.c \
		$(SRC_DIR)/execution/player.c \
		$(SRC_DIR)/execution/textures.c \
		$(SRC_DIR)/execution/hooks.c \
		$(SRC_DIR)/utils/math_utils.c \
		$(SRC_DIR)/utils/movements.c \
		$(SRC_DIR)/utils/free_utils.c \
		$(SRC_DIR)/utils/ft_exit.c \
		$(SRC_DIR)/utils/file_checks_utils.c \
		$(SRC_DIR)/utils/colour.c \
		$(SRC_DIR)/utils/map_checks_utils.c \
		$(SRC_DIR)/utils/init_t_data.c \
		$(SRC_DIR)/utils/init_game.c \
		$(SRC_DIR)/utils/scene_util.c \
		$(SRC_DIR)/utils/rotation.c \

OBJ := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRC:.c=.o))
DEPS := $(OBJ:.o=.d)

LIBFT := my_libft/libft/libft.a
FT_PRINTF := my_libft/ft_printf/ft_printf.a
GNL := my_libft/gnl/gnl.a
MINILIBX := minilibx-linux/libmlx_Linux.a

CC := cc
CFLAGS := -Wall -Wextra -Werror -g3 -I$(INCLUDE) #-O3 
DEPFLAGS := -MMD -MP

RM := rm -rf

#Name has to be the first one to be checked and executed
$(NAME): $(OBJ) $(LIBFT) $(FT_PRINTF) $(GNL) $(MINILIBX)
		@$(CC) $(CFLAGS) $^ -I$(INCLUDE) -Imlx_linux -O3 -Lmlx -lm -L/usr/lib -Imlx_linux -lXext -lX11 -lm -o $(NAME)
		@printf "${GREEN}-----------------Created $(NAME)---------------------${RESET}\n"
		
$(OBJ): $(OBJ_DIR)%.o:$(SRC_DIR)%.c
		@mkdir -p $(OBJ_DIR)
		@mkdir -p $(OBJ_DIR)/execution
		@mkdir -p $(OBJ_DIR)/parsing
		@mkdir -p $(OBJ_DIR)/utils
		@$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@
		@printf "${CYAN} ~ Compiled -> ${MAGENTA}%s ${RESET}\n" "$<"

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

clean:
		@make clean -C my_libft/libft
		@make clean -C my_libft/ft_printf
		@make clean -C my_libft/gnl
		@make clean -C minilibx-linux
		@$(RM) $(OBJ) $(OBJ_DIR)
		@printf "${RED}------------------Cleaned $(OBJ_DIR) directory-------------${RESET}\n"

fclean: clean
		@make fclean -C my_libft/libft
		@make fclean -C my_libft/ft_printf
		@make fclean -C my_libft/gnl
		@make clean -C minilibx-linux
		@$(RM) $(NAME)
		@printf "${RED}------------------Cleaned $(NAME) library------------------${RESET}\n"

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re 
