/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_preproc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:47:33 by mel-haya          #+#    #+#             */
/*   Updated: 2021/12/03 10:30:47 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*untokenize_env(char *name)
{
	char	*ret;
	char	*value;
	t_env	*e;
	int		i;

	i = 0;
	e = get_env_by_name(name);
	if (!e)
		return (NULL);
	value = e->value;
	if (!value)
		return (NULL);
	ret = ft_strdup(value);
	while (ret[i])
	{
		if (ret[i] == '$' || ret[i] == '|' || ret[i] == '<' || ret[i] == '>')
			ret[i] = -ret[i];
		i++;
	}
	return (ret);
}

char	*tokenize_line(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] < 0)
			line[i] = -line[i];
		i++;
	}
	return (line);
}
