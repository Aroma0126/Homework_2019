//
// Created by 樊玲君 on 2019/9/30.
//

/*The client send a message to server,and receives another message from
server*/
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define MSGKEY 75
struct msgform                  /*定义消息结构*/
{
    ong mtype;
    char mtext[256];
};
main()
{
    struct msgform msg;
    int msgqid,pid,*pint;
    msgqid=msgget(MSGKEY,0777);                 /*建立消息队列*/
    pid=getpid();
    pint=(int *)msg.mtext;
    *pint=pid;
    msg.mtype=1;                                /*定义消息类型*/
    msgsnd(msgqid,&msg,sizeof(int),0);          /*发送消息*/
    msgrcv(msgqid,&msg,256,pid,0);              /*接受从服务者发来的消息*/
    printf("Clint : receive from pid %d\n",* pint);
}
