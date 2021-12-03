#include "../execution.h"

int	exec_env(char **cmd)
{
	t_env	*tmp;

	if (arr_lenght(cmd) == 1)
	{
		tmp = g_shell.env;
		while (tmp->next != NULL)
		{
			if(tmp->value)
				printf("%s=%s\n", tmp->name, tmp->value);
			tmp = tmp->next;
		}
		if(tmp->value)
			printf("%s=%s\n", tmp->name, tmp->value);
	}
	return (0);
}
