NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./include -I/usr/local/include
LIBS = -lreadline

SRC_DIR = src
OBJ_DIR = obj
SRCS = $(SRC_DIR)/main.c \
		$(SRC_DIR)/utils/init.c \
		$(SRC_DIR)/utils/output.c \
		$(SRC_DIR)/utils/string.c \
		$(SRC_DIR)/utils/error.c \
		$(SRC_DIR)/utils/env.c \
		$(SRC_DIR)/utils/numbers.c \
		$(SRC_DIR)/signals/signals.c \
		$(SRC_DIR)/parser/parse.c \
		$(SRC_DIR)/lexer/token.c \
		$(SRC_DIR)/lexer/utils.c \
		$(SRC_DIR)/lexer/tokenize.c \
		$(SRC_DIR)/parser/expand.c \
		$(SRC_DIR)/executor/execute.c \
		$(SRC_DIR)/executor/path.c \
		$(SRC_DIR)/executor/pipes.c \
		$(SRC_DIR)/executor/redirections.c \
		$(SRC_DIR)/builtins/echo.c \
		$(SRC_DIR)/builtins/cd.c \
		$(SRC_DIR)/builtins/pwd.c \
	   $(SRC_DIR)/builtins/export.c \
	   $(SRC_DIR)/builtins/export_utils.c \
	   $(SRC_DIR)/builtins/print_env_sorted.c \
		$(SRC_DIR)/builtins/unset.c \
		$(SRC_DIR)/builtins/env.c \
		$(SRC_DIR)/builtins/exit.c \
		$(SRC_DIR)/utils/missing_stubs.c \
		$(SRC_DIR)/utils/ident.c \
		$(SRC_DIR)/utils/init_shell.c \
		$(SRC_DIR)/utils/split.c \
		$(SRC_DIR)/utils/quote_utils.c \
		$(SRC_DIR)/utils/expand_utils.c

OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
