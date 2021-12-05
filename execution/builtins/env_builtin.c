/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:25:32 by mhalli            #+#    #+#             */
/*   Updated: 2021/12/04 14:25:35 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	exec_env(char **cmd)
{
	t_env	*tmp;

	if (arr_lenght(cmd) == 1)
	{
		tmp = g_shell.env;
		while (tmp->next != NULL)
		{
			if (tmp->value)
				printf("%s=%s\n", tmp->name, tmp->value);
			tmp = tmp->next;
		}
		if (tmp->value)
			printf("%s=%s\n", tmp->name, tmp->value);
	}
	return (0);
}
