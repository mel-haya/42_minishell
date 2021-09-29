#include "minishell.h"

int remove_char(char *str,int index, int flag)
{
	int i;

	i = 0;
	if(!flag)
		flag = str[index];
	else
		flag = 0;
	while (str[index + i])
	{
		str[index + i] = str[index + i + 1];
		i++;
	}
	return (flag);
}

int	remove_str(char **str,int i,int count)
{
	int len;
	char *after;
	char	*new;

	len = ft_strlen(*str) - count + 1;
	new = malloc(len);
	after = *str + i + count;
	(*str)[i] = 0;
	ft_strlcpy(new, *str, i + 1);
	ft_strlcpy(new + i, after, ft_strlen(after) + 1);
	free(*str);
	*str = new;
	return 0;
}