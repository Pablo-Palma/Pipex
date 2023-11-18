NAME = libft.a
LIBFT_SRC_DIR = src
PRINTF_SRC_DIR = printf
GNL_SRC_DIR = get_next_line
OBJ_DIR = obj
INC_DIR = inc
LIBFT_SRC = $(wildcard $(LIBFT_SRC_DIR)/*/*.c)
PRINTF_SRC = $(wildcard $(PRINTF_SRC_DIR)/*.c)
GNL_SRC = $(wildcard get_next_line/*.c)
MAND_SRC_DIR = mand
BONUS_SRC =	$(wildcard $(LIBFT_SRC_DIR)/bonus/*.c)

SRC = $(LIBFT_SRC) $(PRINTF_SRC) $(GNL_SRC)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

FLAGS =	-Wall -Werror -Wextra -I$(INC_DIR)

.PHONY: all	clean	fclean	re	bonus

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

bonus: all $(BONUS_OBJ)
	@ar rcs $(NAME) $(OBJ) $(BONUS_OBJ)
	@echo "Libft bonus compiled succesfully!"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@gcc $(FLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/$(LIBFT_SRC_DIR) $(OBJ_DIR)/$(PRINTF_SRC_DIR) $(OBJ_DIR/$(GNL_SRC_DIR)))

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)

re: fclean all
