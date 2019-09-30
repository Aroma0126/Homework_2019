

#include "stdio.h"
#include "time.h"
#include "stdlib.h"
#include "unistd.h"

/**
 * 子进程是如何产生的？ 调用fork产生的
 * 又是如何结束的？ 当定义其return 0; 时结束
 * 子进程被创建后它的运行环境是怎样建立的？ 跟随父进程
**/

int main() {

    int i;
    if (fork())
    {
        i = wait();
        printf("It is parent process\n");
        printf("The child process,id number %d is finished\n",i);
    }
    else
    {
        printf("It is child process\n");
        sleep(10);
        exit(0);
    }
    return 0;
}