#ifndef EXECUTION_H
# define EXECUTION_H
# include <stdio.h>
# include <sys/errno.h>
# include "../libft/libft.h"
# include "../minishell.h"

// typedef struct	s_env
// {
// 	char			*key; 
// 	char			*value; 
// 	struct s_env	*next;
// }                   t_env;

//--------------NODE UTILS----------------//

// void	delete_node(t_env *lst, t_env *target);

// //------- MINISHELL UTILS FUNCTIONS --------//

char    *get_path();
int     is_builtin(char *cmd);
void	exec_builtin(char **cmd);
int     arr_lenght(char **arr);
// void	free_arr(char **arr);

// //------ KEY VALUE FUNCTIONS ------------//
// int	find_key(t_env *env, char *target);
// char	*get_key_value(t_env *env, char *key_target);
// void	change_key_value(t_env *env, char *key_target, char *new_value);
// void	add_key_value(t_env *env, char *key, char *value);

// //------- LIST CONSTRUCTOR FUNCTIONS --------//

// t_env	*init_node(char *key, char *value);
// t_env	*get_lastnode(t_env *lst);
// void	add_node(t_env **lst, t_env *new_node);

// //------- LIST DESTRUCTOR FUNCTIONS --------//

// void	free_lst(t_env **lst);
void	exit_err(char *msg, int status, int fd);

// //------- BUILTINS FUNCTIONS --------//

void	exec_echo(char **cmd);
void	exec_pwd();
void	exec_cd(char **cmd);
void	exec_export(char **cmd);
void	exec_unset(char **cmd);
void	exec_env(char **cmd);
void	exec_exit(char **cmd);

//merged version
void	execution();

#endif