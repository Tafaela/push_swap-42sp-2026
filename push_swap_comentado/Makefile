NAME		= push_swap
BONUS_NAME	= checker

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I include

SRC_DIR		= src
SRC			= main.c strategy.c stack_utils.c stack_utils2.c \
			  ft_str.c ft_nbr.c ft_atoi.c parse.c disorder.c \
			  rotate_utils.c operations_swap.c operations_push.c \
			  operations_rotate.c operations_rrotate.c \
			  sort_helpers1.c sort_helpers2.c sort_helpers3.c \
			  sort_simple.c sort_simple_three.c sort_medium.c \
			  sort_medium2.c sort_complex.c sort_complex_radix.c \
			  sort_complex_cost.c sort_complex_move.c \
			  sort_complex_insert.c sort_adaptive.c benchmark.c

OBJ			= $(addprefix $(SRC_DIR)/, $(SRC:.c=.o))

BONUS_DIR	= src_bonus
BONUS_SRC	= checker_bonus.c stack_utils_bonus.c ft_utils_bonus.c \
			  ft_atoi_bonus.c gnl_bonus.c parse_bonus.c \
			  operations_bonus.c operations_bonus2.c

BONUS_OBJ	= $(addprefix $(BONUS_DIR)/, $(BONUS_SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ) -o $(BONUS_NAME)

$(BONUS_DIR)/%.o: $(BONUS_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all bonus clean fclean re
