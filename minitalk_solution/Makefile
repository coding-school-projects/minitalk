CLIENT = client
SERVER = server

CLIENT_BONUS = client_bonus
SERVER_BONUS = server_bonus

CLIENT_CFILE = client.c
SERVER_CFILE = server.c

CLIENT_BONUS_CFILE = ./bonus/client_bonus.c
SERVER_BONUS_CFILE = ./bonus/server_bonus.c

CLIENT_OFILE = $(CLIENT_CFILE:.c=.o)
SERVER_OFILE = $(SERVER_CFILE:.c=.o)

CLIENT_BONUS_OFILE = $(CLIENT_BONUS_CFILE:.c=.o)
SERVER_BONUS_OFILE = $(SERVER_BONUS_CFILE:.c=.o)

RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
RESET=\033[0m

CFLAG = -Wall -Werror -Wextra

RM = rm -rf

all : $(CLIENT) $(SERVER) bonus

bonus: $(SERVER_BONUS) $(CLIENT_BONUS)
	@ echo "$(GREEN)Successfully minitalk compiled."
	@ echo "$(GREEN)Server And Client Are Ready!"

norm: 
	norminette $(CLIENT_CFILE) $(SERVER_CFILE) $(CLIENT_BONUS_CFILE) $(SERVER_BONUS_CFILE)

$(CLIENT) : $(CLIENT_OFILE)
	@ gcc $(CFLAG) $(CLIENT_OFILE) -o $(CLIENT)

$(SERVER) : $(SERVER_OFILE)
	@ gcc $(CFLAG) $(SERVER_OFILE) -o $(SERVER)

$(CLIENT_BONUS) : $(CLIENT_BONUS_OFILE)
	@ gcc $(CFLAG) $(CLIENT_BONUS_OFILE) -o $(CLIENT_BONUS)

$(SERVER_BONUS) : $(SERVER_BONUS_OFILE)
	@ gcc $(CFLAG) $(SERVER_BONUS_OFILE) -o $(SERVER_BONUS)

clean:
	@ $(RM) $(CLIENT_OFILE) $(SERVER_OFILE) $(CLIENT_BONUS_OFILE) $(SERVER_BONUS_OFILE)
	@ echo "$(RED)minitalk object files cleaned!"

fclean: clean
	@ $(RM) $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)
	@ echo "$(RED)Server and Client have Been Cleaned Successfully!"

re: fclean all

.PHONY: all clean fclean re bonus
