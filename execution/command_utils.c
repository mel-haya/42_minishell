/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:27:20 by mhalli            #+#    #+#             */
/*   Updated: 2021/12/10 16:06:19 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			lenght++;
			tmp = tmp->next;
		}
		return (lenght);
	}
	return (lenght);
}

char	*fill_line(char *name, char *value)
{
	char	*str;
	char	*tmp;

	tmp = ft_strjoin(name, "=");
	if (value)
		str = ft_strjoin(tmp, value);
	else
		str = ft_strdup(name);
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
		if (!env)
			return (NULL);
		tmp = g_shell.env;
		while (tmp)
		{
			env[i] = fill_line(tmp->name, tmp->value);
			if (tmp->next == NULL)
			{
				env[i + 1] = NULL;
				return (env);
			}
			tmp = tmp->next;
			i++;
		}
	}
	return (NULL);
}
