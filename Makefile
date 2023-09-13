NAME_CLIENT = client
NAME_SERVER = server

FLAGS = -Wall -Wextra -Werror
LIB_FLAGS = -L./libft -lft

all: client server

client: libft42 $(NAME_CLIENT)
	gcc $(FLAGS)  $(SRC_CLIENT) src/client.c $(LIB_FLAGS) -o $(NAME_CLIENT)

server: libft42 $(NAME_SERVER)
	gcc $(FLAGS) $(SRC_SERVER) src/server.c $(LIB_FLAGS)   -o $(NAME_SERVER)


clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME_CLIENT) $(NAME_SERVER)
	make -C libft fclean

re: fclean all

# Run the command 'make -C libft' at the beginning
libft42:
	make -C libft

.PHONY: all clean fclean re