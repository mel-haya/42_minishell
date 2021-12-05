/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 16:44:54 by mhalli            #+#    #+#             */
/*   Updated: 2021/12/04 16:44:55 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_path_exist(void)
{
	t_env	*tmp;

	if (g_shell.env)
	{
		tmp = g_shell.env;
		while (tmp)
		{
			if (!strcmp(tmp->name, "PATH"))
				return (1);
			if (tmp->next == NULL)
				break ;
			tmp = tmp->next;
		}
	}
	return (0);
}

char	*path_case_error(void)
{
	if (is_path_exist())
		return (ft_strdup("command not found"));
	else
		return (ft_strdup("No such file or directory"));
}

char	*get_path(void)
{
	t_env	*tmp;

	if (g_shell.env)
	{
		tmp = g_shell.env;
		while (tmp)
		{
			if (!strcmp(tmp->name, "PATH"))
				return (ft_strdup(tmp->value));
			if (tmp->next == NULL)
				break ;
			tmp = tmp->next;
		}
	}
	return (NULL);
}

int	arr_lenght(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	get_exitvalue(int ret)
{
	if (WIFEXITED(ret))
		return (WEXITSTATUS(ret));
	else if (WIFSIGNALED(ret))
		return (128 + WTERMSIG(ret));
	return (ret);
}
