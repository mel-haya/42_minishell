#include "minishell.h"

void global_sig_handler(int sig)
{
	if(sig == SIGINT && !g_shell.is_forked)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("",0);
		rl_redisplay();
	}
	else if(sig == SIGINT && g_shell.is_forked)
		printf("\n");
}

void heredoc_sig_handler(int sig)
{
    if(sig == SIGINT && g_shell.is_forked)
    {
        printf("\n");
        exit(1);
    }
}

void set_global_signals()
{
	signal(SIGINT, global_sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
