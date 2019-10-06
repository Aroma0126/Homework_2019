//
// Created by 樊玲君 on 2019/9/30.
//


#include <stdio.h>
#include <nistd.h>

/* 父进程向子进程发送18 号软中断信号后等待。子进程收到信号，执行指定的程
序，再将父进程唤醒。*/
/**
 * 这就是软中断信号处理，有点儿明白了吧？讨论一下它与硬中断有什么区
    别？看来还挺管用，好好利用它。
 *
 * **/

int main()
{
    int i,j,k;
    int func();
    signal(18,func()); /*设置18 号信号的处理程序*/
    if(i=fork())            /*创建子进程*/
    {                       /*父进程执行*/
        j=kill(i,18);       /*向子进程发送信号*/
        printf("Parent: signal 18 has been sent to child %d,returned %d.\n",i,j);
        k=wait();                   /*父进程被唤醒*/
        printf("After wait %d,Parent %d: finished.\n",k,getpid());
    }
    else
    {                                                           /*子进程执行*/
        sleep(10);
        printf("Child %d: A signal from my parent is recived.\n",getpid());
    }                                           /*子进程结束，向父进程发子进程结束信号*/
}

void func()                                          /*处理程序*/
{
    int m;
    m=getpid();
    printf("I am Process %d: It is signal 18 processing function.\n",m);
}
