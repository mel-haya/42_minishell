
all:
	$(MAKE) -C libft/
	gcc minishell.c env.c args.c utils.c libft/libft.a heredoc.c -lreadline -o minishell -g