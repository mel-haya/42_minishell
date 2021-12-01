/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:28:57 by mourad            #+#    #+#             */
/*   Updated: 2021/11/30 16:48:41 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	global_sig_handler(int sig)
{
	if (sig == SIGINT && !g_shell.is_forked)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	// else if (sig == SIGINT && g_shell.is_forked)
	// {
	// 	//printf("\n");
	// 	return ;
	// }
	//printf("%d\n", g_shell.is_forked);
}

void	heredoc_sig_handler(int sig)
{
	if (sig == SIGINT && g_shell.is_forked)
	{
		printf("\n");
		exit(1);
	}
}

void	set_global_signals(void)
{
	signal(SIGINT, global_sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ignctl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
