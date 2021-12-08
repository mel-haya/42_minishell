/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:27:20 by mhalli            #+#    #+#             */
/*   Updated: 2021/12/06 17:27:21 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	get_listlenght(t_env *env)
{
	t_env	*tmp;
	int		lenght;

	lenght = 0;
	if (env)
	{
		tmp = g_shell.env;
		while (tmp)
		{
			if (tmp->next == NULL)
				return (lenght);
			tmp = tmp->next;
			if (tmp->value)
				lenght++;
		}
	}
	return (lenght);
}

char	*fill_line(char *name, char *value)
{
	char	*str;
	char	*tmp;

	tmp = ft_strjoin(name, "=");
	str = ft_strjoin(tmp, value);
	free(tmp);
	return (str);
}

char	**construct_env(void)
{
	t_env	*tmp;
	char	**env;
	int		i;

	i = 0;
	if (g_shell.env)
	{
		env = malloc(sizeof(char *) * (get_listlenght(g_shell.env) + 1));
		tmp = g_shell.env;
		while (tmp)
		{
			if (tmp->value)
				env[i] = fill_line(tmp->name, tmp->value);
			if (tmp->next == NULL)
			{
				env[i] = NULL;
				return (env);
			}
			tmp = tmp->next;
			if (tmp->value)
				i++;
		}
	}
	return (NULL);
}
