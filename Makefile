NAME = minishell

LIBS = libft/libft.a

FLAGS = -Wall -Wextra -Werror

LDFLAGS= -L /Users/$(USER)/goinfre/$(USER)/.brew/opt/readline/lib
CPPFLAGS= -I /Users/$(USER)/goinfre/$(USER)/.brew/opt/readline/include
READLINE = -lreadline $(LDFLAGS) $(CPPFLAGS)

SANITIZE = -fsanitize=address -g

SRC = execution/execution.c execution/utils.c execution/lst_constructor.c execution/lst_destructor.c \
	execution/builtins/echo_builtin.c execution/builtins/pwd_builtin.c execution/builtins/cd_builtin.c \
	execution/builtins/export_builtin.c execution/builtins/unset_builtin.c execution/builtins/env_builtin.c \
	execution/builtins/exit_builtin.c execution/builtins/builtins.c execution/builtins/builtins_utils.c\
	execution/redirections/redirections.c execution/redirections/redirections_utils.c \
	execution/pipes.c execution/command_exec.c execution/command_utils.c \
	\
	libft/ft_atoi.c\
	libft/ft_bzero.c\
	libft/ft_calloc.c\
	libft/ft_isalnum.c\
	libft/ft_isalpha.c\
	libft/ft_isascii.c\
	libft/ft_isdigit.c\
	libft/ft_isprint.c\
	libft/ft_itoa.c\
	libft/ft_memccpy.c\
	libft/ft_memchr.c\
	libft/ft_memcmp.c\
	libft/ft_memcpy.c\
	libft/ft_memmove.c\
	libft/ft_memset.c\
	libft/ft_putchar_fd.c\
	libft/ft_putendl_fd.c\
	libft/ft_putstr_fd.c\
	libft/ft_strchr.c\
	libft/ft_strdup.c\
	libft/ft_strjoin.c\
	libft/ft_strlcat.c\
	libft/ft_strlcpy.c\
	libft/ft_strlen.c\
	libft/ft_strncmp.c\
	libft/ft_strnstr.c\
	libft/ft_strrchr.c\
	libft/ft_tolower.c\
	libft/ft_toupper.c\
	libft/ft_split.c\
	\
	minishell.c env.c args.c utils.c heredoc.c free_all.c redirection_parse.c signals.c line_preproc.c env1.c utils1.c\

all: $(NAME)

tmp:
	mkdir tmp

$(NAME): tmp
	@gcc $(SRC) -lreadline -o $(NAME) $(READLINE) $(FLAGS)

clean:
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME) $(NAME).dSYM #TODO: remove

re: fclean all
