NAME = pipex
CC = gcc -g3
CFLAGS = -Wall -Werror -Wextra -I libft/inc
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
SRC_DIR = src/
OBJ_DIR = obj/
SHARED_SRC = get_path.c command_split.c
MAND_SRC = mand/main.c mand/execute.c mand/utils.c mand/parser.c
BONUS_SRC = bonus/main_bonus.c bonus/execute_bonus.c bonus/utils_bonus.c bonus/parser_bonus.c
SHARED_OBJ = $(addprefix $(OBJ_DIR), $(SHARED_SRC:.c=.o))

SRC = $(if $(BONUS),$(BONUS_SRC),$(MAND_SRC))
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o)) $(SHARED_OBJ)

all: $(NAME)

bonus: 
	@$(MAKE) BONUS=1

$(NAME): $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "libft compiled successfully!"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT_LIB)
	@echo "pipex compiled successfully!"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c -I inc $< -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)shared/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c -I inc $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -rf $(OBJ_DIR)
	@echo "Object files removed!"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "Executable and object files removed!"

re: fclean all

.PHONY: all bonus clean fclean re
