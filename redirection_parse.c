/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:09:21 by mourad            #+#    #+#             */
/*   Updated: 2021/12/03 11:08:29 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_last_red(t_command *cmd, t_redirection	*red)
{
	if (red->token == '>')
		cmd->red_out = red;
	else
		cmd->red_in = red;
}

int	check_red_token(char **str, int i)
{
	char	*red;
	char	c;

	c = (*str)[i];
	red = *str;
	if (red[i] == red[i + 1])
		i++;
	i++;
	while (red[i] == ' ')
		i++;
	if (is_token(red[i]))
	{
		printf("minishell : syntax error near unexpected token '%c'\n", c);
		g_shell.status = 1;
		return (0);
	}
	else
		return (1);
}

int	get_redirections(char **str, t_command *cmd, int i)
{
	t_redirection	*tmp;

	while ((*str)[i] && (*str)[i] != '|')
	{
		while ((*str)[i] == ' ')
			i++;
		if ((*str)[i] == '<' || (*str)[i] == '>')
		{
			if (!check_red_token(str, i))
				return (-1);
			aloc_red(cmd, &tmp);
			if ((get_redirection(str, tmp, i)) == -1)
			{
				tmp->next = NULL;
				return (-1);
			}
			get_last_red(cmd, tmp);
			tmp->next = NULL;
		}
		else
			i = skip_arg(*str, i);
	}
	return (0);
}

int	init_red(char **str, t_redirection *r, int i)
{
	int	j;

	j = i + 1;
	r->token = (*str)[i];
	if ((*str)[j] == (*str)[i])
		r->append = 1;
	else
		r->append = 0;
	j += r->append;
	while ((*str)[j] == ' ')
		j++;
	if (is_token((*str)[j]))
	{
		printf("minishell :syntax error near unexpected token\
'%c'\n", (*str)[j]);
		return (-1);
	}
	return (j);
}

int	get_redirection(char **str, t_redirection *r, int i)
{
	int	j;
	int	len;

	j = init_red(str, r, i);
	if (j == -1)
		return (-1);
	len = skip_arg(*str, j);
	r->file = malloc(len - j + 1);
	ft_strlcpy(r->file, (*str) + j, len - j + 1);
	if (r->token == '<' && r->append)
		r->file = here_doc(r->file);
	if (!r->file)
		return (-1);
	remove_quotes(&(r->file));
	remove_str(str, i, len - i);
	if (!check_file(r))
		return (-1);
	return (0);
}
