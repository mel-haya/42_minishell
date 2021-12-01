/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:32:40 by mourad            #+#    #+#             */
/*   Updated: 2021/11/30 17:21:28 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	is_empty_line(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (!str[i])
		return (1);
	else
		return (0);
}

int	remove_char(char *str, int index, int flag)
{
	int	i;

	i = 0;
	if (!flag)
		flag = str[index];
	else
		flag = 0;
	while (str[index + i])
	{
		str[index + i] = str[index + i + 1];
		i++;
	}
	return (flag);
}

int	remove_str(char **str, int i, int count)
{
	int		len;
	char	*after;
	char	*new;

	len = ft_strlen(*str) - count + 1;
	new = malloc(len);
	after = *str + i + count;
	(*str)[i] = 0;
	ft_strlcpy(new, *str, i + 1);
	ft_strlcpy(new + i, after, ft_strlen(after) + 1);
	free(*str);
	*str = new;
	return (0);
}

int	is_token(char c)
{
	if (c == ' ' || c == '|' || c == '<' || c == '>')
		return (1);
	else
		return (0);
}

int	check_file(t_redirection *r)
{
	int	fd;

	fd = open(r->file, O_RDONLY, 0644);
	close(fd);
	if (fd == -1 && r->token == '>')
	{
		fd = open(r->file, O_RDONLY | O_CREAT, 0644);
		close(fd);
		return(1);
	}
	else if (fd == -1)
	{
		printf("minishell: %s: No such file or directory\n", r->file);
		return (0);
	}
	else
		return (1);
}
