#include "../execution.h"

int exec_pwd()
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, 1);
	return (0);
}