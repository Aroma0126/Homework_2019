

#include <unistd.h>
#include <stdio.h>

int main()
{
    printf("my pid is %d,my father's pid is %d\n",getpid(),getppid());
    for (int i = 0;i < 3;i++) //一共有1 + 2 + 4 + 8 = 15个进程
    {
        if (fork() == 0)
            printf("%d pid = %d ppid = %d\n",i,getpid(),getppid());
        else
        {
            int j = wait(0);
            printf("%d: the child %d is finished.\n",j,getpid());
        }
    }
}

/**
 *  画出进程的家族树。
 *  子进程的运行环境是怎样建立的？反复运行此程序看会有什么情况？解释一下。
 *
 *  修改程序，使运行结果呈单分支结构，即每个父进程只产生一个子进
 *  程。画出进程树，解释该程序。
 *
**/