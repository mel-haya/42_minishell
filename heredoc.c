/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourad <mourad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 02:37:35 by mourad            #+#    #+#             */
/*   Updated: 2021/10/26 15:50:34 by mourad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_delimeter(char *str)
{
	int	flag;
	int	i;
	int	mode;

	i = 0;
	mode = 0;
	flag = 0;
	while (str[i])
	{
		if (!flag && (str[i] == 39 || str[i] == 34))
		{
			flag = remove_char(str, i, flag);
			mode = 1;
		}
		else if (flag && str[i] == flag)
			flag = remove_char(str, i, flag);
		else
			i++;
	}
	if (flag)
		return (-1);
	return (mode);
}

void	expand_line(char **line)
{
	int	i;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$')
			expand_env(line, i);
		else
			i++;
	}
}

int	input_to_file(char *file, char *delimeter, int mode)
{
	char	*line;
	int		fd;

	g_shell.is_forked = 1;
	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	while (1)
	{
		line = readline("heredoc>");
		if (!line)
			printf("\n");
		if (!line || !ft_strncmp(line, delimeter, ft_strlen(line)))
			break ;
		if (!mode)
			expand_line(&line);
		write(fd, line, ft_strlen(line));
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

char	*here_doc(char *str)
{
	int		mode;
	int		pid;
	char	*file;

	mode = get_delimeter(str);
	file = here_doc_name();
	if (mode == -1)
	{
		printf("Error : Multiline\n");
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
	{
		unlink(file);
		return (NULL);
	}
	set_global_signals();
	return (file);
}
