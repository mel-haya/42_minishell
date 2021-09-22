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
    struct s_command *next;
}               t_command;

typedef struct s_env
{
    char    *name;
    char    *value;
    struct s_env   *next;
}               t_env;

int skip_arg(char *cmd, int i)
{
    char flag;

    flag = 0;
    while (cmd[i])
    {
        if (!flag && (cmd[i] == ' ' || cmd[i] == '|'))
            return i;
        if (!flag && (cmd[i] == 34 || cmd[i] == 39))
        {
            flag = cmd[i];
            i++;
        }
        else if (flag == cmd[i + 1])
            flag = 0;
        i++;
    }
    return i;
}
int get_args_num(char *cmd)
{
    int i;
    int args;

    args = 0;
    i = 0;
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

// char *get_args(char *cmd, t_command *cmds)
// {
//     int i;
//     int j;
//     int skip;

//     j = 0;
//     i = 0;
//     cmds->args = malloc(sizeof(char *) * (get_args_num(line) + 1));
//     while(cmd[i] == ' ')
//         i++;
//     while(cmd[i])
//     {
//         skip = skip_arg(cmd, i);
//         cmds->args[j] = malloc(skip - i + 1);
//         ft_strlcpy(cmds->args[j],)
        
//     }

// }

int env_name_len(char *env)
{
    int i;

    i = 0;
    while(env[i] != '=')
        i++;
    return (i);
}

void fill_env(char **envp, t_env *env)
{
    int i;
    t_env *tmp;
    int name_size;

    tmp = env;
    i = 0;
    while(envp[i])
    {
        name_size = env_name_len(envp[i]);
        tmp->name = malloc(name_size + 2);
        tmp->value = malloc(ft_strlen(envp[i]) - name_size + 1);
        ft_strlcpy(tmp->name, envp[i], name_size + 2);
        printf("%s \n", tmp->name);
        ft_strlcpy(tmp->value, envp[i] + name_size + 2, ft_strlen(envp[i]) - name_size + 1);
        if(envp[i + 1])
        {
            env->next = malloc(sizeof(t_env *));
            env = env->next;
        }
        else
            env->next = NULL;
        i++;
    }
}

void print_env(t_env *e)
{
    t_env *env = e;
    while(env)
    {
        printf("%s = %s\n",env->name, env->value);
        env = env->next;
    } 
}

int main (int argc, char **argv, char **envp)
{

    t_command   *cmds;
    t_env       *env;
    char        *line;
    
    char *s[] = {"echo", NULL};
    env = malloc(sizeof(t_env *));
    fill_env(envp, env);
    //print_env(env);
    while(1)
    {
        line = readline("$>");
        printf("%d\n", get_args_num(line));
        int id = fork();
        if(id != 0)
            wait(NULL);
        else
        {
            execve(line,NULL,envp);
            return 0;
        }
    }
    return 0;
}