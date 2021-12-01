#include "../execution.h"

int	is_option(char *cmd)
{
	int		i;

	i = 0;
	if (cmd[i] == '-' && ft_strlen(cmd) > 1)
	{
		i++;
		while (cmd[i])
		{
			if (cmd[i] != 'n')
				return (0);
			i++;
		}
	}
	return (i);
}

int	toprint(char **cmd, int option)
{
	int		i;

	i = 1;
	while (option && cmd[i])
	{
		if (!is_option(cmd[i]))
			return (i);
		i++;
	}
	return (i);
}

void	exec_echo(char **cmd)
{
    int		option;
	int		index;
    
	if (arr_lenght(cmd) > 1)
	{
    	option = is_option(cmd[1]);
		index = toprint(cmd, option);
		while (cmd[index])
		{
			ft_putstr_fd(cmd[index], 1);
			if (cmd[index + 1] != NULL)
					ft_putstr_fd(" ", 1);
			index++;
		}
		if (!option)
			ft_putchar_fd('\n', 1);
	}
	else
		ft_putchar_fd('\n', 1);
}