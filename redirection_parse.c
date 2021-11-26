/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourad <mourad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:09:21 by mourad            #+#    #+#             */
/*   Updated: 2021/10/26 18:13:46 by mourad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	aloc_red(t_command *cmd, t_redirection	**tmp)
{
	if (!cmd->redirection)
	{
		cmd->redirection = malloc(sizeof(t_redirection));
		*tmp = cmd->redirection;
	}
	else
	{
		(*tmp)->next = malloc(sizeof(t_redirection));
		*tmp = (*tmp)->next;
	}
}

void	get_last_red(t_command *cmd, t_redirection	*red)
{
	if (red->token == '>')
		cmd->red_out = red;
	else
		cmd->red_in = red;
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
		printf("syntax error near unexpected token '%c'\n", (*str)[j]);
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
