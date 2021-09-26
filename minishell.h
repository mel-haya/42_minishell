#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"


typedef struct s_command
{
	char **args;
	int i;
	struct s_command *next;
}               t_command;

typedef struct s_env
{
	char    *name;
	char    *value;
	struct s_env   *next;
}               t_env;

typedef struct  s_global
{
	t_command   *cmds;
	t_env       *env;
	int         status;
}               t_global;

t_global g_shell;

t_env   *get_env_by_name(char *name);
int     env_name_len(char *env);
void    fill_env(char **envp);
void    print_env();
int     replace_env(char **arg, int index);

#endif