#include "minishell.h"


int get_delimeter(char *str)
{
    int flag;
    int i;
    int mode;

    i = 0;
    mode = 0;
    flag = 0;
    while(str[i])
    {
        if (!flag && (str[i] == 39 || str[i] == 34))
        {
            flag = remove_char(str, i, flag);;
            mode = 1;  
        }
        else if (flag && str[i] == flag)
            flag = remove_char(str, i, flag);
        else
            i++;
    }
    if (flag)
        return (-1);
    return mode;
}

void expand_line(char **line)
{
    int i;

    i = 0;
    while((*line)[i])
    {
        if((*line)[i] == '$')
            expand_env(line,i);
        else
            i++;
    }
}

int input_to_file(int fd, char *delimeter, int mode)
{
    char *line;
    
    g_shell.is_forked = 1;
    while(1)
    {
        line = readline("heredoc>");
        if(!line)
        {
            printf("\nminishell: warning: here-document at line 12 delimited by end-of-file (wanted '%s')\n",delimeter);
            return 1;
        }
        if(!ft_strncmp(line,delimeter,ft_strlen(line)))
            return 0;
        if(!mode)
            expand_line(&line);
        write(fd, line,ft_strlen(line));
        free(line);
        write(fd, "\n",1);
    }
}

char *here_doc_name()
{
    char *tmp;
    char *ret;

    tmp = ft_itoa(g_shell.heredocn);
    ret = ft_strjoin("tmp/.", tmp);
    g_shell.heredocn++;
    free(tmp);
    return ret;
}

char *here_doc(char *str)
{
    int mode;
    int fd;
    int pid;
    char *file;

    fd = 0;
    mode = get_delimeter(str);
    file = here_doc_name();
    if(mode == -1)
    {
        printf("Error : Multiline\n");
        return (NULL);
    }
    signal(SIGINT, heredoc_sig_handler);
    pid = fork();
    if(!pid)
    {
        fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
        input_to_file(fd, str, mode);
        close(fd);
        exit(0);
    }
    else
        wait(&g_shell.status);
    if(g_shell.status)
        return NULL;
    free(str);
    set_global_signals();
    return file;
}
