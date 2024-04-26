SERVER = server
CLIENT = client
SERVER_B = server_bonus
CLIENT_B = client_bonus


PRINTF = ./ft_printf/libftprintf.a

SRC_S = server.c
SRC_C = client.c
CBONUS = client_bonus.c minitalk_utils.c
SBONUS = server_bonus.c

OBJ_S = ${SRC_S:.c=.o}
OBJ_C = ${SRC_C:.c=.o}
OBJ_BS = $(SBONUS:.c=.o)
OBJ_BC = $(CBONUS:.c=.o)

CC = cc
CFLAGS = -Werror -Wextra -Wall
NAME = $(SERVER) $(CLIENT) $(SERVER_B) $(CLIENT_B)

all : $(SERVER) $(CLIENT) 

$(CLIENT) : $(OBJ_C) $(PRINTF)
	$(CC) $(OBJ_C) $(PRINTF) -o $(CLIENT)

$(SERVER) : $(OBJ_S) $(PRINTF)
	$(CC) $(OBJ_S) $(PRINTF) -o $(SERVER)


%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@


bonus: $(SERVER_B) $(CLIENT_B)

$(SERVER_B) : $(OBJ_BS) $(PRINTF)
	$(CC) $(OBJ_BS) $(PRINTF) -o $(SERVER_B) 

$(PRINTF) : 
	MAKE -C ./ft_printf

$(CLIENT_B) : $(OBJ_BC) $(PRINTF)
	$(CC) $(OBJ_BC) $(PRINTF) -o $(CLIENT_B)

clean: 
	rm -f $(OBJ_C) $(OBJ_S) $(OBJ_BC) $(OBJ_BS)
	make clean -C ./ft_printf 

fclean: clean
	rm -f $(SERVER) $(CLIENT) $(SERVER_B) $(CLIENT_B)
	make fclean -C ./ft_printf
	
re: fclean  all 

.PHONY: all clean fclean re bonus

.SECONDARY: $(OBJ_S) $(OBJ_C) $(OBJ_BS) $(OBJ_BC)