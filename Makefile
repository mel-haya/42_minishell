
all:
	$(MAKE) -C libft/
	gcc minishell.c libft/libft.a -lreadline -o minishell -g