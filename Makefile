.PHONY: all clean fclean re asan

NAME			= minitalk
SERVER			= server
CLIENT			= client
SERVER_BONUS	= server_bonus
CLIENT_BONUS	= client_bonus

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf
INCLUDES	= ./includes
LIBFTPRINTF	= -lftprintf

SRCS_DIR		= ./src
SRCS_DIR_BONUS	= ./src/bonus
OBJS_DIR		= ./obj
LIBS_DIR		= ./libs

SERVER_SRCS 		= $(addprefix $(SRCS_DIR)/, server.c)
CLIENT_SRCS 		= $(addprefix $(SRCS_DIR)/, client.c)
SERVER_SRCS_BONUS	= $(addprefix $(SRCS_DIR_BONUS)/, server_bonus.c)
CLIENT_SRCS_BONUS	= $(addprefix $(SRCS_DIR_BONUS)/, client_bonus.c)

SERVER_OBJS			= $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SERVER_SRCS))
CLIENT_OBJS			= $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(CLIENT_SRCS))
SERVER_OBJS_BONUS	= $(patsubst $(SRCS_DIR_BONUS)/%.c,$(OBJS_DIR)/%.o,$(SERVER_SRCS_BONUS))
CLIENT_OBJS_BONUS	= $(patsubst $(SRCS_DIR_BONUS)/%.c,$(OBJS_DIR)/%.o,$(CLIENT_SRCS_BONUS))

all: $(NAME)

$(SERVER): $(SERVER_OBJS) $(INCLUDES)/minitalk.h $(INCLUDES)/libftprintf.h $(INCLUDES)/libft.h
	$(CC) $(CFLAGS) $(SERVER_OBJS) -o $(SERVER) -L$(LIBS_DIR) $(LIBFTPRINTF) -I$(INCLUDES)

$(CLIENT): $(CLIENT_OBJS) $(INCLUDES)/minitalk.h $(INCLUDES)/libftprintf.h $(INCLUDES)/libft.h
	$(CC) $(CFLAGS) $(CLIENT_OBJS) -o $(CLIENT) -L$(LIBS_DIR) $(LIBFTPRINTF) -I$(INCLUDES)
	
$(SERVER_BONUS): $(SERVER_OBJS_BONUS) $(INCLUDES)/minitalk.h $(INCLUDES)/libftprintf.h $(INCLUDES)/libft.h
	$(CC) $(CFLAGS) $(SERVER_OBJS_BONUS) -o $(SERVER_BONUS) -L$(LIBS_DIR) $(LIBFTPRINTF) -I$(INCLUDES)

$(CLIENT_BONUS): $(CLIENT_OBJS_BONUS) $(INCLUDES)/minitalk.h $(INCLUDES)/libftprintf.h $(INCLUDES)/libft.h
	$(CC) $(CFLAGS) $(CLIENT_OBJS_BONUS) -o $(CLIENT_BONUS) -L$(LIBS_DIR) $(LIBFTPRINTF) -I$(INCLUDES)
	
$(NAME): $(SERVER) $(CLIENT)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

$(OBJS_DIR)/%.o: $(SRCS_DIR_BONUS)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean: 
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(SERVER) $(CLIENT)

re: fclean all

bonus: $(SERVER_BONUS) $(CLIENT_BONUS)