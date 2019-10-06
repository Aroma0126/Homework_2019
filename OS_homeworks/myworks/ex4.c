//
// Created by 樊玲君 on 2019/9/25.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int global = 4;

int main()
{
    pid_t pid;
    int var_i = 5;
    printf("before fork.\n");
    if ( (pid = fork()) < 0 )
    {
        printf("fork error.\n");
        exit(0);
    }
    else
    {
        if( pid == 0 )
        {                                               /*子进程执行*/
            global++;
            var_i--;
            printf("Child %d changed the vari and globa.\n",getpid());
        }
        else                                            /*父进程执行*/
            printf("Parent %d did not changed the vari and globa.\n",getpid());
    }

    printf("pid = %d, global = %d, var_i = %d\n",getpid(),global,var_i); /*都执行*/
    exit(0);
}