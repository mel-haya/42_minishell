/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:20:30 by mourad            #+#    #+#             */
/*   Updated: 2021/12/03 11:02:03 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_after(char *str, char *after, int index)
{
	after = str + index + 1;
	if (is_token(*after))
		return (after);
	if ((!ft_isalpha(*after) && *after != '_'))
		return (after + 1);
	while (*after && (*after != 34 && *after != 39 \
	&& *after != ' ' && *after != '$'))
		after++;
	return (after);
}

int	expand_env(char **arg, int index)
{
	char	*after;
	int		len;
	char	*value;
	char	*new;

	if ((*arg)[index + 1] == '?')
		return (expand_status(arg, index));
	value = untokenize_env((*arg) + index + 1);
	if (!value)
		value = ft_strdup("");
	after = get_after(*arg, after, index);
	len = index + ft_strlen(value) + ft_strlen(after) + 2;
	new = malloc(len);
	ft_strlcpy(new, *arg, index + 1);
	ft_strlcpy(new + index, value, ft_strlen(value) + 1);
	ft_strlcpy(new + index + ft_strlen(value), after, ft_strlen(after) + 1);
	free(*arg);
	len = index + ft_strlen(value);
	free(value);
	*arg = new;
	return (len);
}

int	get_delimeter(char *str)
{
	int	flag;
	int	i;
	int	mode;

	i = 0;
	mode = 0;
	flag = 0;
	while (str[i])
	{
		if (!flag && (str[i] == 39 || str[i] == 34))
		{
			flag = remove_char(str, i, flag);
			mode = 1;
		}
		else if (flag && str[i] == flag)
			flag = remove_char(str, i, flag);
		else
			i++;
	}
	if (flag)
		return (-1);
	return (mode);
}

void	expand_line(char **line)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$' && !flag)
			i = expand_env(line, i);
		else
		{
			if ((*line)[i] == '\'' && flag)
				flag = 0;
			if ((*line)[i] == '\'' && !flag)
				flag = 1;
			i++;
		}
	}
}
