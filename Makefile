.PHONY: all clean fclean re asan

SERVER		= server
CLIENT		= client

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf
INCLUDES	= ./includes
LIBFTPRINTF	= -lftprintf

SRCS_DIR	= ./src
OBJS_DIR	= ./obj
LIBS_DIR	= ./libs
UTILS_DIR	= ./utils

SERVER_SRCS 		= $(addprefix $(SRCS_DIR)/, server.c)
UTILS_SERVER_SRCS	= $(addprefix $(UTILS_DIR)/, )
CLIENT_SRCS 		= $(addprefix $(SRCS_DIR)/, client.c)
UTILS_CLIENT_SRCS	= $(addprefix $(UTILS_DIR)/, )

SERVER_OBJS		= $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SERVER_SRCS))
SERVER_OBJS		+= $(patsubst $(UTILS_DIR)/%.c,$(OBJS_DIR)/%.o,$(UTILS_SRCS))
CLIENT_OBJS		= $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(CLIENT_SRCS))
CLIENT_OBJS		+= $(patsubst $(UTILS_DIR)/%.c,$(OBJS_DIR)/%.o,$(UTILS_SRCS))

all: $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OBJS) $(INCLUDES)/minitalk.h $(INCLUDES)/libftprintf.h $(INCLUDES)/libft.h
	$(CC) $(CFLAGS) $(SERVER_OBJS) -o $(SERVER) -L$(LIBS_DIR) $(LIBFTPRINTF) -I$(INCLUDES)
	
$(CLIENT): $(CLIENT_OBJS) $(INCLUDES)/minitalk.h $(INCLUDES)/libftprintf.h $(INCLUDES)/libft.h
	$(CC) $(CFLAGS) $(CLIENT_OBJS) -o $(CLIENT) -L$(LIBS_DIR) $(LIBFTPRINTF) -I$(INCLUDES)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

$(OBJS_DIR)/%.o: $(UTILS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean: 
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(SERVER) $(CLIENT)

re: fclean all