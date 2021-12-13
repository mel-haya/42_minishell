/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:25:32 by mhalli            #+#    #+#             */
/*   Updated: 2021/12/10 16:08:41 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_env(char **cmd)
{
	t_env	*tmp;

	if (arr_lenght(cmd) == 1)
	{
		tmp = g_shell.env;
		while (tmp && tmp->next != NULL)
		{
			if (tmp->value)
				printf("%s=%s\n", tmp->name, tmp->value);
			tmp = tmp->next;
		}
		if (tmp && tmp->value)
			printf("%s=%s\n", tmp->name, tmp->value);
	}
	return (0);
}
