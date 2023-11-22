NAME = pipex
BONUS_NAME = pipex_bonus
CC = gcc -g3
CFLAGS = -Wall -Werror -Wextra -I libft/inc
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
SRC_DIR = src/
SHARED_SRC = get_path.c command_split.c
MAND_SRC = main.c execute.c utils.c parser.c 
BONUS_SRC = main_bonus.c execute_bonus.c utils_bonus.c parser_bonus.c
OBJ_DIR = obj/
MAND_OBJ = $(addprefix $(OBJ_DIR), $(MAND_SRC:.c=.o))
BONUS_OBJ = $(addprefix $(OBJ_DIR), $(BONUS_SRC:.c=.o))
SHARED_OBJ = $(addprefix $(OBJ_DIR), $(SHARED_SRC:.c=.o))

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(MAND_OBJ) $(SHARED_OBJ)
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "libft compiled successfully!"
	@$(CC) $(CFLAGS) -o $(NAME) $(MAND_OBJ) $(SHARED_OBJ) $(LIBFT_LIB)
	@echo "pipex compiled successfully!"

$(BONUS_NAME): $(BONUS_OBJ) $(SHARED_OBJ)
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "libft compiled successfully!"
	@$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJ) $(SHARED_OBJ) $(LIBFT_LIB)
	@echo "pipex bonus compiled successfully!"

$(OBJ_DIR)%.o: $(SRC_DIR)mand/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c -I inc $< -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)bonus/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -DBONUS -c -I inc $< -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)shared/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c -I inc $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "object files removed!"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME) $(BONUS_NAME)
	@echo "Executable and objet files removed!"

re: fclean all
	@echo "Recompiled everything!"

.PHONY: all clean fclean re
