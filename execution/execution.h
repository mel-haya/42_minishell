/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 17:04:10 by mhalli            #+#    #+#             */
/*   Updated: 2021/12/04 17:04:12 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include <stdio.h>
# include <sys/errno.h>
# include "../libft/libft.h"
# include "../minishell.h"

char	*get_path(void);
int		is_builtin(char *cmd);
int		exec_builtin(char **cmd);
int		arr_lenght(char **arr);
void	exit_err(char *msg, char *output, int fd);

int		exec_echo(char **cmd);
int		exec_pwd(void);
int		exec_cd(char **cmd);
int		exec_export(char **cmd);
int		exec_unset(char **cmd);
int		exec_env(char **cmd);
void	exec_exit(char **cmd);

void	execution(void);

void	fds_saver(int *fds, int lock);

char	*path_case_error(void);
int		is_path_exist(void);

int		get_exitvalue(int ret);

void	pipes(void);

void	exec_cmd(char *path, char **cmd, char *err_output);

void	free_arr(char **arr);

#endif
