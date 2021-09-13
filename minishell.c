#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>





int main (int argc, char **argv, char **envp)
{

    char *s[] = {"echo",NULL};
    int exit = 0;
    while(!exit)
    {
        int id = fork();
        if(id != 0)
            wait(NULL);
        else
        {
            execve("/bin/pwd",s,envp);
            return 0;
        }
    }
    return 0;
}