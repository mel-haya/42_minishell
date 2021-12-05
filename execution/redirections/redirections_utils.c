/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 16:21:16 by mhalli            #+#    #+#             */
/*   Updated: 2021/12/04 16:21:20 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	append_redir(t_redirection *redir)
{
	int	out;

	out = open(redir->file,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (out == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(redir->file);
		close(out);
		return (0);
	}
	close(out);
	return (1);
}

int	out_redir(t_redirection *redir)
{
	int	out;

	out = open(redir->file,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(redir->file);
		close (out);
		return (0);
	}
	close (out);
	return (1);
}

int	in_redir(t_redirection *redir)
{
	int	in;

	in = open(redir->file, O_RDONLY);
	if (in == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(redir->file);
		close (in);
		return (0);
	}
	close (in);
	return (1);
}

int	filter_redir(t_redirection *redirs)
{
	t_redirection	*tmp;
	int				err_status;

	tmp = redirs;
	while (tmp)
	{
		if (tmp->token == '>' && tmp->append)
			err_status = append_redir(tmp);
		else if (tmp->token == '<')
			err_status = in_redir(tmp);
		else if (tmp->token == '>')
			err_status = out_redir(tmp);
		if (err_status == 0)
			return (0);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return (1);
}

void	fds_saver(int *fds, int lock)
{
	if (lock == 0)
	{
		fds[0] = dup(0);
		fds[1] = dup(1);
	}
	else
	{
		dup2(fds[0], 0);
		dup2(fds[1], 1);
	}
}
