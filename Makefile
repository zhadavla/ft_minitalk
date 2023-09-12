NAME_CLIENT = client
NAME_SERVER = server

SRC_DIR = src
BONUS_DIR = bonus

# Recursively find all .c files in SRC_DIR and its subdirectories
SOURCES_SR = src/client.c
SOURCES_CL = src/server.c

# CFLAGS = -Wall -Wextra -Werror
LIBFLAGS = -L./libft -lft -ldl -pthread -lm
MY_HEADER = ft_minitalk.h

OBJ_DIR = obj

OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:$(SRC_DIR)/%.c=%.o))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	gcc $(CFLAGS) -I $(MY_HEADER) -c $< -o $@

$(NAME_CLIENT): obj/client.o
	cc $(CFLAGS) -o $(NAME_CLIENT) obj/client.o $(LIBFLAGS)

$(NAME_CLIENT): obj/client.o
cc $(CFLAGS) -o $(NAME_CLIENT) obj/client.o $(LIBFLAGS)

$(OBJ_DIR):
	mkdir -p $(dir $(OBJECTS))   # Create subdirectories in OBJ_DIR

all: libft $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

# Run the command 'make -C libft' at the beginning
libft:
	make -C libft

.PHONY: all clean fclean re