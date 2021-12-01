#include "execution.h"

void	append_redir(t_redirection *redir)
{
	int	out;

	out = open(redir->file,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (out == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(redir->file);
	}
	close(out);
}

void	out_redir(t_redirection *redir)
{
	int	out;

	out = open(redir->file,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(redir->file);
	}
	close (out);
}

void	in_redir(t_redirection *redir)
{
	int	in;

	in = open(redir->file, O_RDONLY);
	if (in == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(redir->file);
	}
	close(in);
}

void	filter_redir(t_redirection *redirs)
{
	t_redirection *tmp;
	// int		err_status;

	tmp = redirs;

	while (tmp)
	{
		if (tmp->token == '>' && tmp->append)
			append_redir(tmp);
		else if (tmp->token == '<')
			in_redir(tmp);
		else if (tmp->token == '>')
			out_redir(tmp);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
}