#include "../execution.h"

char	*get_export_key(char *str)
{
	char	*key;
	int		i;

	i = 1;
	// if (!ft_strchr(str, '='))
	// 	return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	key = (char *)malloc(sizeof(char) * (i + 1));
	i = -1;
	while (str[++i] != '=')
		key[i] = str[i];
	key[i] = 0;
	return (key);
}

char	*get_export_value(char *str)
{
	char	*value;
	int		i;

	i = 0;
	// if (!ft_strchr(str, '='))
	// 	return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	value = ft_strdup(str + i + 1);
	return (value);
}

// int		filter_key(char *str)
// {
// 	int		i;
	
// 	i = -1;
// 	if (str && ft_isdigit(str[0]))
// 		return (0);
// 	while (str && str[++i])
// 	{
// 		if (!ft_isalnum(str[i]) && str[i] != '=')
// 			return (0);
// 	}
// 	return (1);
// }

int		is_valid_data(char *data)
{
	int		i;

	i = 0;
	if ((ft_isalpha(data[i]) || data[i] == '_'))
	{
		while(data[++i])
		{
			if (!ft_isalnum(data[i]) && data[i] != '=' && data[i] != '_')
				return (0);
		}
		return (1);
	}
	return(0);
}

void	exec_export(char **cmd)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (cmd[++i])
	{
		if (is_valid_data(cmd[i]))
		{
			if (!ft_strchr(cmd[i], '='))
				return ;
			key = get_export_key(cmd[i]);
			value = get_export_value(cmd[i]);
			add_key_value(g_shell.env, key, value);
		}
		else
			printf("minishell: %s: `%s': not a valid identifier\n", cmd[0], cmd[i]);
	}
	// char	*key;
	// char	*value;
	// int		i;

	// i = 0;
	// while (cmd[++i])
	// {
	// 	key = get_export_key(cmd[i]);
	// 	if (cmd[i][0] && filter_key(key))
	// 	{
	// 		value = get_export_value(cmd[i]);
	// 		add_key_value(g_shell.env, key, value);
	// 	}
	// 	else
	// 	{
	// 		free(key);
	// 		printf("minishell: %s: `%s': not a valid identifier\n", cmd[0], cmd[i]);
	// 	}
	// }
}
