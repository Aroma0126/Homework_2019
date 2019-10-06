//
// Created by 樊玲君 on 2019/9/30.
//

/*服务者程序*/
/*The server receives the message from client,and answer a message*/
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#define MSGKEY 75

struct msgform                  /*定义消息结构*/
{
    long mtype;
    char mtext[256];
} msg;

int msgqid;

int main()
{
    int i,pid,* pint;
    extern cleanup();
    for(i=0;i<20;i++)
        signal(i,cleanup);              /*设置软中断信号的处理程序*/
    msgqid=msgget(MSGKEY,0777|IPC_CREAT);       /*建立消息队列*/
    for(;;)                                /*等待接受消息*/
    {
        msgrcv(msgqid,&msg,256,1,0); /* 接受消息*/
        pint=(int *)msg.mtext;
        pid=*pint;
        printf("Server :receive from pid %d\n",pid);    /*显示消息来源*/
        msg.mtype=pid;
        *pint=getpid();                             /*加入自己的进程标识*/
        msgsnd(msgqid,&msg,sizeof(int),0);          /*发送消息*/
    }
}
void cleanup()
{
    msgctl(msgqid,IPC_RMID,0);
    exit();
}
