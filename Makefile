
all:
	$(MAKE) -C libft/
	gcc minishell.c env.c args.c utils.c libft/libft.a heredoc.c -lreadline -L /goinfre/mel-haya/.brew/opt/readline/lib -I /goinfre/mel-haya/.brew/opt/readline/include -o minishell -g