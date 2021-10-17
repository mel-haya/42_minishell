
# all:
# 	@$(MAKE) -C libft/ --no-print-directory
# 	@gcc minishell.c env.c args.c utils.c heredoc.c libft/libft.a -lreadline -o minishell -g



NAME = minishell

LIBS = libft/libft.a

FLAGS = -Wall -Wextra -Werror

SANITIZE = -fsanitize=address -g

SRC = execution/execution.c execution/utils.c execution/lst_constructor.c execution/lst_destructor.c \
	execution/builtins/echo_builtin.c execution/builtins/pwd_builtin.c execution/builtins/cd_builtin.c \
	execution/builtins/export_builtin.c execution/builtins/unset_builtin.c execution/builtins/env_builtin.c \
	execution/builtins/exit_builtin.c \
	\
	minishell.c env.c args.c utils.c heredoc.c signals.c\

all: $(NAME)

$(NAME):
	$(MAKE) -C libft/
	@gcc $(SRC) -lreadline libft/libft.a -o $(NAME) -g


clean:
	$(MAKE) -C libft/ fclean
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME) $(NAME).dSYM #TODO: remove

re: fclean all	