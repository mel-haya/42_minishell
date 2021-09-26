
all:
	$(MAKE) -C libft/
	gcc minishell.c env.c libft/libft.a -lreadline -o minishell -g