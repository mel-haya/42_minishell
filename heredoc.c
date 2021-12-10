/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 02:37:35 by mourad            #+#    #+#             */
/*   Updated: 2021/12/03 10:29:31 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_to_file(char *file, char *delimeter, int mode)
{
	char	*line;
	int		fd;

	g_shell.is_forked = 1;
	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	while (1)
	{
		line = readline(">");
		if (!line || !ft_strncmp(line, delimeter, ft_strlen(line) \
			+ ft_strlen(delimeter)))
			break ;
		if (!*line)
			continue ;
		if (!mode)
			expand_line(&line);
		write(fd, tokenize_line(line), ft_strlen(line));
		free(line);
		write(fd, "\n", 1);
	}
	close(fd);
	exit(0);
}

char	*here_doc_name(void)
{
	char	*tmp;
	char	*ret;

	tmp = ft_itoa(g_shell.heredocn);
	ret = ft_strjoin("tmp/.", tmp);
	g_shell.heredocn++;
	free(tmp);
	return (ret);
}

char	*failed_herdoc(char *file)
{
	g_shell.status = 1;
	unlink(file);
	free(file);
	return (NULL);
}

char	*here_doc(char *str)
{
	int		mode;
	int		pid;
	char	*file;

	mode = get_delimeter(str);
	file = here_doc_name();
	if (mode == -1)
	{
		printf("minishell : Unclose quotes\n");
		g_shell.status = 1;
		return (NULL);
	}
	signal(SIGINT, heredoc_sig_handler);
	pid = fork();
	if (!pid)
		input_to_file(file, str, mode);
	else
		wait(&g_shell.status);
	free(str);
	if (g_shell.status)
		return (failed_herdoc(file));
	set_global_signals();
	return (file);
}
