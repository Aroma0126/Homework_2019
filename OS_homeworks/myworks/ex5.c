//
// Created by 樊玲君 on 2019/9/25.
//
/**
 *
 *什么是管道？
 * 进程如何利用它进行通信的？解释一下实现方法。
    修改睡眠时机、睡眠长度，看看会有什么变化。请解释。
    ③加锁、解锁起什么作用？不用它行吗？

 * **/

#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int i, r, j, k, l, p1, p2, fd[2];
    char buf[50], s[50];
    pipe(fd);                               /*建立一个管道fd*/
    while ((p1 = fork()) == -1);
    if (p1 == 0)                               /*创建子进程1*/
    {
        lockf(fd[1], 1, 0);                /*子进程1 执行*//*管道写入端加锁*/
        sprintf(buf, "Child process P1 is sending messages! \n");
        printf("Child process P1! \n");
        write(fd[1], buf, 50);                /*信息写入管道*/
        lockf(fd[1], 0, 0);                   /*管道写入端解锁*/
        sleep(5);
        j = getpid();
        k = getppid();
        printf("P1 %d is weak up. My parent process ID is %d.\n", j, k);
        exit(0);
    }
    else
    {
        while ((p2 = fork()) == -1);     /*创建子进程2*/
        if (p2 == 0)
        {                                               /*子进程2 执行*/
            lockf(fd[1], 1, 0);                        /*管道写入端加锁*/
            sprintf(buf, "Child process P2 is sending messages! \n");
            printf("Child process P2! \n");
            write(fd[1], buf, 50);                   /*信息写入管道*/
            lockf(fd[1], 0, 0);                       /*管道写入端解锁*/
            sleep(5);
            j = getpid();
            k = getppid();
            printf("P2 %d is weak up. My parent process ID is %d.\n", j, k);
            exit(0);
        }
        else
        {
            l = getpid();
            wait(0);
            if (r = read(fd[0], s, 50) == -1)
                printf("Can't read pipe. \n");
            else
                printf("Parent %d: %s \n", l, s);
            wait(0);
            if (r = read(fd[0], s, 50) == -1)
                printf("Can't read pipe. \n");
            else
                printf("Parent %d: %s \n", l, s);
            exit(0);
        }
    }
}