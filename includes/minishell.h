/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:11:51 by mel-haya          #+#    #+#             */
/*   Updated: 2021/12/11 23:46:24 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <curses.h>
# include <term.h>
# include <termcap.h>
# include <unistd.h>
# include <signal.h>
# include <termios.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/errno.h>
# include "execution.h"

typedef struct s_redirection
{
	char					*file;
	char					token;
	int						append;
	struct s_redirection	*next;
}				t_redirection;

typedef struct s_command
{
	char				**args;
	t_redirection		*redirection;
	t_redirection		*red_in;
	t_redirection		*red_out;
	int					is_piped;
	struct s_command	*next;
}						t_command;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_global
{
	int			is_forked;
	t_command	*cmds;
	t_env		*env;
	int			status;
	int			heredocn;
	int			_savein;
	int			_saveout;
}			t_global;

t_global	g_shell;

t_env	*get_env_by_name(char *name);
int		env_name_len(char *env);
void	fill_env(char **envp);
int		expand_env(char **arg, int index);
int		quote_args(t_command *cmd);
int		get_args(char *cmd, t_command *new);
int		get_args_num(char *cmd);
int		skip_arg(char *cmd, int i);
int		remove_char(char *str, int index, int flag);
int		remove_str(char **str, int i, int count);
int		get_redirection(char **str, t_redirection *r, int i);
int		get_redirections(char **str, t_command *cmd, int i);
char	*here_doc(char *str);
void	set_global_signals(void);
void	heredoc_sig_handler(int sig);
void	global_sig_handler(int sig);
void	ignctl(void);
int		is_token(char c);
int		check_file(t_redirection *r);
int		remove_quotes(char **s);
void	free_redirection(void);
void	free_cmds(void);
int		is_empty_line(char *str);
char	*untokenize_env(char *name);
char	*tokenize_line(char *line);
void	expand_line(char **line);
int		get_delimeter(char *str);
int		init_global(void);
void	aloc_red(t_command *cmd, t_redirection	**tmp);
int		get_exitvalue(int ret);
int		filter_redir(t_redirection *redirs);
int		find_key(t_env *env, char *target);
void	change_key_value(t_env *env, char *key_target, char *new_value);
char	*get_key_value(t_env *env, char *key_target);
void	add_key_value(t_env *env, char *key, char *value);
int		expand_status(char **arg, int index);
void	add_node(t_env **lst, t_env *new_node);
t_env	*init_node(char *key, char *value);
int		command_exec(t_command *cmd);
void	redir_exec(t_command *cmd);
void	exit_malloc_fail(void);
void	free_env(void);
void	revertctl(void);

#endif
