SERVER = server

CLIENT = client

SRC_S = server.c 

SRC_C = client.c

CC = gcc

CFLAGS = -Werror -Wextra -Wall

all : $(SERVER) $(CLIENT) clean

OBJ_S = ${SRC_S:.c=.o}

OBJ_C = ${SRC_C:.c=.o}

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
 
$(SERVER) : $(OBJ_S)
	$(CC) $(OBJ_S) -o $(SERVER)

$(CLIENT) : $(OBJ_C)
	$(CC) $(OBJ_S) -o $(CLIENT)

clean: 
	rm -f $(OBJ_C) $(OBJ_S)

fclean: clean
	rm -f $(SERVER) $(CLIENT)

re: fclean all
