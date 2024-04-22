SERVER = server

CLIENT = client

SERVER_B = server_bonus

CLIENT_B = client_bonus

SRC_S = server.c

SRC_C = client.c

CBONUS = client_bonus.c

SBONUS = server_bonus.c

CC = gcc

CFLAGS = -Werror -Wextra -Wall

all : $(SERVER) $(CLIENT)

bonus: $(SERVER_B) $(CLIENT_B) clean

OBJ_S = ${SRC_S:.c=.o}

OBJ_C = ${SRC_C:.c=.o}

OBJ_BS = $(SBONUS:.c=.o)

OBJ_BC = $(CBONUS:.c=.o)

$(SERVER_B) : $(OBJ_BS)
	$(CC) $(OBJ_BS) -o $(SERVER_B)

$(CLIENT_B) : $(OBJ_BC)
	$(CC) $(OBJ_BC) -o $(CLIENT_B)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
 
$(SERVER) : $(OBJ_S)
	$(CC) $(OBJ_S) -o $(SERVER)

$(CLIENT) : $(OBJ_C)
	$(CC) $(OBJ_C) -o $(CLIENT)

clean: 
	rm -f $(OBJ_C) $(OBJ_S) $(OBJ_BC) $(OBJ_BS)

fclean: clean
	rm -f $(SERVER) $(CLIENT) $(SERVER_B) $(CLIENT_B)

re: fclean  all 

.PHONY: all clean fclean re bonus