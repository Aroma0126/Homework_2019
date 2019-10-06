//
// Created by 樊玲君 on 2019/9/23.
//

#include <stdio.h>
#include <unistd.h>

/**
 * 子进程运行其它程序后，进程运行环境怎样变化的？反复运行此程序看会有什么情况？解释一下。
 **/

int main()
{
    int child_pid1,child_pid2,child_pid3;// 定义子进程
    int pid,status;
    setbuf(stdout,NULL);

    child_pid1 = fork(); /*创建子进程1*/
    if (child_pid1 == 0)
    {
        execlp("echo","echo","child process 1",(char *)0); /*子进程1 启动其它程序*/
        // linux-echo:输出文字到控制台
        perror("exec1 error.\n ");
        // 把一个描述性错误消息输出到标准错误 stderr。首先输出字符串 str，后跟一个冒号，然后是一个空格。
        exit(1);
    }

    child_pid2 = fork(); /*创建子进程2*/
    if(child_pid2 == 0)
    {
        execlp("date","date",(char *)0); /*子进程2 启动其它程序*/
        perror("exec2 error.\n ");
        exit(2);
    }

    child_pid3 = fork(); /*创建子进程3*/
    if(child_pid3 == 0)
    {
        execlp("ls","ls",(char *)0); /*子进程3 启动其它程序*/
        perror("exec3 error.\n ");
        exit(3);
    }

    puts("Parent process is waiting for child process return!");

    while((pid = wait(&status)) != -1)                         /*等待子进程结束*/
    {
        if(child_pid1 == pid)                                  /*若子进程1 结束*/
            printf("child process 1 terminated with status %d\n",(status>>8));
        else if (child_pid2 == pid)                            /*若子进程2 结束*/
            printf("child process 2 terminated with status %d\n",(status>>8));
        else if(child_pid3 == pid)                             /*若子进程3 结束*/
            printf("child process 3 terminated with status %d\n" ,(status>>8));
    }

    puts("All child processes terminated.");
    puts("Parent process terminated.");
    exit(0);
}
