
all:
	$(MAKE) -C libft/
	gcc minishell.c env.c args.c utils.c libft/libft.a -lreadline -o minishell -g -fsanitize=address