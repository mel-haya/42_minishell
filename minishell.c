#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"


typedef struct s_command
{
    char **args;
    int i;
}               t_command;
int skip_arg(char *cmd, int i)
{
    char flag;

    flag = 0;
    while (cmd[i])
    {
        if (!flag && (cmd[i] == ' ' || cmd[i] == '|'))
            return i;
        if (!flag && (cmd[i] == 34 || cmd[i] == 39))
            flag = cmd[i];
        else if (flag == cmd[i])
            flag = 0;
        i++;
    }
    return i;
}
int get_args_num(char *cmd)
{
    int i;
    int args;

    args++;
    while(cmd[i] == ' ')
        i++;
    while(cmd[i])
    {
        i = skip_arg(cmd, i);
        args++;
        while(cmd[i] == ' ')
            i++;
        if(cmd[i] == '|')
            return args;
    }
    return args;
}

char *get_args(char *cmd)
{
    int i;
    int j;
    int flag;
    i = 0;
}

char

int main (int argc, char **argv, char **envp)
{

    char *s[] = {"echo",NULL};
    char *line;
    int exit = 0;
    while(!exit)
    {
        line = readline("$>");
        int id = fork();
        if(id != 0)
            wait(NULL);
        else
        {
            execve(line,s,envp);
            return 0;
        }
    }
    return 0;
}