#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct	s_redirection
{
	char	*file;
	char	token;
	int		append;
	struct s_redirection *next;
	
}				t_redirection;


typedef struct s_command
{
	char **args;
	t_redirection *redirection;
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
	int is_forked;
	t_command   *cmds;
	t_env       *env;
	int         status;
	int			heredocn;
}               t_global;

t_global g_shell;

t_env   *get_env_by_name(char *name);
int     env_name_len(char *env);
void    fill_env(char **envp);
void    print_env();
int     expand_env(char **arg, int index);
void	quote_args(t_command *cmd);
int		get_args(char *cmd, t_command *new);
int		get_args_num(char *cmd);
int		skip_arg(char *cmd, int i);
int		remove_char(char *str,int index, int flag);
int		remove_str(char **str,int i,int count);
int		get_redirection(char **str, t_redirection *r, int i);
int		get_redirections(char **str, t_command *cmd, int i);
int		new_env(char *name, char *value);
char	*here_doc(char *str);
void set_global_signals();

#endif