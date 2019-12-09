#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>
#include<time.h>
#include<string.h>
#include <sys/types.h>
// #include <sys/syscall.h>
#define PNUM  5 //进程的数量
int timenow=0;     //当前时刻
typedef struct node
{
    int pid;
    int priority;                        //1~3,数字越小优先级越高
    int totaltime;                       //CPU区间时间,也就是预计需要的时间
    int rest;                            //剩余时间
    char state;                          // Run, Waiting, True -> 运行，就绪，完成
    struct node *next;
}PCB;

PCB *job;//所有作业的序列,带头节点(为简化编程)
PCB *ready=NULL; //进程就绪队列,不带头节点
PCB *tail=NULL;  //记录就绪队列的尾节点,只有一个
PCB *run=NULL;//正在运行中的进程,不带头结点，只有一个
PCB *finish=NULL;//已经结束的程序,不带头结点

void InitialJob()
{
    int i=0;
    PCB *p,*tail;
    job=(PCB *)malloc(sizeof(PCB));//生成头节点,其它域无意义
    job->next=NULL;
    tail=job;

    for(i=0;i<PNUM;i++)
    {
        p=(PCB *)malloc(sizeof(PCB));//生成新节点(新进程)
        p->pid=i+1;
        p->priority=rand()%3+1;    //随机生成优先级:1~3
        p->totaltime=rand()%8+1;   //随机生成CPU区间时间:1~10;(估计运行时间)
        p->rest=p->totaltime;
        p->state='W';              //初始化进程的状态为'就绪',这里假设都到了，如果是不同时到达还要考虑没到的
        p->next=NULL;
        tail->next=p;
        tail=p;                    //带头结点
    }
}
void DisplayPCB(PCB *pcb) //显示队列
{
    struct node *p=pcb;
    if(pcb == NULL) {printf("PROCESS QUEUE IS NULL!\n");return;}
    printf("ID  PRIORITY  ALLTIME  RESTTIME  STATUS\n");
    do{
        printf("P%-3d\t",p->pid);
        printf("%3d\t",p->priority);
        printf("%3d\t",p->totaltime);
        printf("%3d\t",p->rest);
        printf("%3c\t",p->state);
        printf("\n");
        p=p->next;
    }while(p != NULL);
}

void ReadyQueue(char * algo) //根据作业队列构造就绪队列,algo:算法
{
    struct node *jpre,*jcur,*rpre,* rcur;
    int a=0;
    if(strcmp(algo,"RR") == 0)
        a=0;
    else if(strcmp(algo,"Priority") == 0)
        a=1;
    else
    {
        printf("ReadyQueue()函数调用参数错误!\n");
        exit(0);
    }
    if(job->next == NULL)
    {
        return;
    }
    jpre = job;// 注意！！第一个是头结点，要绕开它!!!
    jcur = job->next;
    while(jcur  !=  NULL) //遍历作业序列中选择已到达进程,将其从作业队列移入就绪队列,直到作业队列为空
    {
        printf("P%d到达.\n",jcur->pid);
        jpre->next = jcur->next;  //将jcur从作业队列移除
        jcur->state = 'W';//将进程状态设置为就绪
        if(ready  ==  NULL) //就绪队列为空
        {
            jcur->next=NULL;
            ready=jcur;
            tail=ready;
        }
        else  //就绪队列不为空,遍历就绪队列,将jcur插入到合适位置
        {
            rpre=ready;
            rcur=ready;
            switch (a)
            {
                case 0:
                    while(rcur != NULL)
                    {rpre=rcur;rcur=rcur->next;}
                    break;
                case 1:  //Priority, Non-Priority,根据优先级查找合适插入点
                    while((rcur != NULL)&&(jcur->priority>=rcur->priority))
                    {
                        rpre=rcur;
                        rcur=rcur->next;
                    }
                    break;
            }
            if (rcur  ==  NULL)// 插入点在就绪队列尾部
            {
                jcur->next=NULL;
                rpre->next=jcur;
                tail=jcur;
            }
            else if (rcur  ==  ready) //插入点在头部
            {
                jcur->next = rcur;
                ready = jcur;
            }
            else //插入到rpre和rcur之间
            {
                jcur->next = rcur;
                rpre->next = jcur;
            }
        }
        jcur = jpre->next;  //下一个作业
    }
    //printf("\n作业队列:\n");
    //DisplayPCB(job->next);
}

void RR()  //时间片
{
    timenow=0;
    while(true)
    {
        printf("\n当前时刻:%d\n",timenow);
        ReadyQueue("RR");
        printf("就绪队列:\n");
        DisplayPCB(ready);

        if(job->next == NULL&&ready == NULL&&run == NULL) break;

        if(ready == NULL)
        {
            tail=NULL;
        }

        if(ready != NULL||run != NULL) //有进程处于就绪或者运行状态
        {
            if(run == NULL) // 若CPU空闲
            {
                run=ready;
                ready=ready->next;
                run->next=NULL;
                printf("\nP%d被调度程序分派CPU!\n",run->pid);
            }
            //count++;

            run->rest--;
            run->state='R';
            printf("\nP%d正在运行.......\n",run->pid);

            if(run->rest == 0)
            {
                printf("\nP%d结束!\n",run->pid);
                run->state = 'T';
                run->next = finish;   //新完成的节点插入到finish的头结点,简单一点
                finish = run;
                run = NULL;
                printf("结束进程队列:\n");
                DisplayPCB(finish);
            }
            else
            {
                if(ready == NULL)
                {
                    ready=run;
                    tail=run;
                    run->state='W';
                    run=NULL;
                }
                else
                {
                    tail->next=run;
                    tail=run;
                    tail->next=NULL;
                    run->state='W';
                    run=NULL;
                    //printf("want to see \n");
                    //DisplayPCB(tail);
                }
            }
        }
        timenow++; //下一时刻继续扫描作业队列
    }
}

void Priority()//抢占式优先级
{
    timenow=0;
    while(true)
    {
        printf("\nCurrent Time:%d\n",timenow);
        ReadyQueue("Priority");//刷新就绪队列
        printf("就绪队列:\n");
        DisplayPCB(ready);
        if(job->next == NULL&&ready == NULL&&run == NULL) break;
        if(ready != NULL||run != NULL) //有进程处于就绪或者运行状态
        {
            if(run == NULL)
            {
                run = ready;      //将CPU分配给ready队列的第一个进程
                ready = ready->next;
                run->next = NULL;
                printf("\nP%d被调度程序分派CPU!\n",run->pid);
            }
            run->rest--;    //修改进程PCB
            run->state='R';
            printf("\nP%d正在运行.......\n",run->pid);
            //printf("运行进程:\n");
            //DisplayPCB(run);
            if(run->rest == 0)
            {
                printf("\nP%d结束!\n",run->pid);
                run->state = 'T';
                run->next = finish;   //新完成的节点插入到finish的头结点,简单一点
                finish = run;
                run = NULL;
                printf("结束进程队列:\n");
                DisplayPCB(finish);
            }
        }
        timenow++; //下一时刻继续扫描作业队列
    }
}
int main()
{
    srand((int)time(NULL)); //随机数种子
    InitialJob();
    DisplayPCB(job->next);
    int s = 1;
    printf("Please type the Algorithm(Priority\\Round Robin):");
    scanf("%d",&s);
    if (s  ==  1)
    {
        Priority();//优先数法
    }
    else
    {
        RR();//简单轮转法
    }
    printf("SYSTEM FINISHED\n");
    return 0;
}
