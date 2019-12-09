#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>
#include<time.h>
#include<string.h>
#include <sys/types.h>
// #include <sys/syscall.h>
#define PNUM  5 //���̵�����
int timenow=0;     //��ǰʱ��
typedef struct node
{
    int pid;
    int priority;                        //1~3,����ԽС���ȼ�Խ��
    int totaltime;                       //CPU����ʱ��,Ҳ����Ԥ����Ҫ��ʱ��
    int rest;                            //ʣ��ʱ��
    char state;                          // Run, Waiting, True -> ���У����������
    struct node *next;
}PCB;

PCB *job;//������ҵ������,��ͷ�ڵ�(Ϊ�򻯱��)
PCB *ready=NULL; //���̾�������,����ͷ�ڵ�
PCB *tail=NULL;  //��¼�������е�β�ڵ�,ֻ��һ��
PCB *run=NULL;//���������еĽ���,����ͷ��㣬ֻ��һ��
PCB *finish=NULL;//�Ѿ������ĳ���,����ͷ���

void InitialJob()
{
    int i=0;
    PCB *p,*tail;
    job=(PCB *)malloc(sizeof(PCB));//����ͷ�ڵ�,������������
    job->next=NULL;
    tail=job;

    for(i=0;i<PNUM;i++)
    {
        p=(PCB *)malloc(sizeof(PCB));//�����½ڵ�(�½���)
        p->pid=i+1;
        p->priority=rand()%3+1;    //����������ȼ�:1~3
        p->totaltime=rand()%8+1;   //�������CPU����ʱ��:1~10;(��������ʱ��)
        p->rest=p->totaltime;
        p->state='W';              //��ʼ�����̵�״̬Ϊ'����',������趼���ˣ�����ǲ�ͬʱ���ﻹҪ����û����
        p->next=NULL;
        tail->next=p;
        tail=p;                    //��ͷ���
    }
}
void DisplayPCB(PCB *pcb) //��ʾ����
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

void ReadyQueue(char * algo) //������ҵ���й����������,algo:�㷨
{
    struct node *jpre,*jcur,*rpre,* rcur;
    int a=0;
    if(strcmp(algo,"RR") == 0)
        a=0;
    else if(strcmp(algo,"Priority") == 0)
        a=1;
    else
    {
        printf("ReadyQueue()�������ò�������!\n");
        exit(0);
    }
    if(job->next == NULL)
    {
        return;
    }
    jpre = job;// ע�⣡����һ����ͷ��㣬Ҫ�ƿ���!!!
    jcur = job->next;
    while(jcur  !=  NULL) //������ҵ������ѡ���ѵ������,�������ҵ���������������,ֱ����ҵ����Ϊ��
    {
        printf("P%d����.\n",jcur->pid);
        jpre->next = jcur->next;  //��jcur����ҵ�����Ƴ�
        jcur->state = 'W';//������״̬����Ϊ����
        if(ready  ==  NULL) //��������Ϊ��
        {
            jcur->next=NULL;
            ready=jcur;
            tail=ready;
        }
        else  //�������в�Ϊ��,������������,��jcur���뵽����λ��
        {
            rpre=ready;
            rcur=ready;
            switch (a)
            {
                case 0:
                    while(rcur != NULL)
                    {rpre=rcur;rcur=rcur->next;}
                    break;
                case 1:  //Priority, Non-Priority,�������ȼ����Һ��ʲ����
                    while((rcur != NULL)&&(jcur->priority>=rcur->priority))
                    {
                        rpre=rcur;
                        rcur=rcur->next;
                    }
                    break;
            }
            if (rcur  ==  NULL)// ������ھ�������β��
            {
                jcur->next=NULL;
                rpre->next=jcur;
                tail=jcur;
            }
            else if (rcur  ==  ready) //�������ͷ��
            {
                jcur->next = rcur;
                ready = jcur;
            }
            else //���뵽rpre��rcur֮��
            {
                jcur->next = rcur;
                rpre->next = jcur;
            }
        }
        jcur = jpre->next;  //��һ����ҵ
    }
    //printf("\n��ҵ����:\n");
    //DisplayPCB(job->next);
}

void RR()  //ʱ��Ƭ
{
    timenow=0;
    while(true)
    {
        printf("\n��ǰʱ��:%d\n",timenow);
        ReadyQueue("RR");
        printf("��������:\n");
        DisplayPCB(ready);

        if(job->next == NULL&&ready == NULL&&run == NULL) break;

        if(ready == NULL)
        {
            tail=NULL;
        }

        if(ready != NULL||run != NULL) //�н��̴��ھ�����������״̬
        {
            if(run == NULL) // ��CPU����
            {
                run=ready;
                ready=ready->next;
                run->next=NULL;
                printf("\nP%d�����ȳ������CPU!\n",run->pid);
            }
            //count++;

            run->rest--;
            run->state='R';
            printf("\nP%d��������.......\n",run->pid);

            if(run->rest == 0)
            {
                printf("\nP%d����!\n",run->pid);
                run->state = 'T';
                run->next = finish;   //����ɵĽڵ���뵽finish��ͷ���,��һ��
                finish = run;
                run = NULL;
                printf("�������̶���:\n");
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
        timenow++; //��һʱ�̼���ɨ����ҵ����
    }
}

void Priority()//��ռʽ���ȼ�
{
    timenow=0;
    while(true)
    {
        printf("\nCurrent Time:%d\n",timenow);
        ReadyQueue("Priority");//ˢ�¾�������
        printf("��������:\n");
        DisplayPCB(ready);
        if(job->next == NULL&&ready == NULL&&run == NULL) break;
        if(ready != NULL||run != NULL) //�н��̴��ھ�����������״̬
        {
            if(run == NULL)
            {
                run = ready;      //��CPU�����ready���еĵ�һ������
                ready = ready->next;
                run->next = NULL;
                printf("\nP%d�����ȳ������CPU!\n",run->pid);
            }
            run->rest--;    //�޸Ľ���PCB
            run->state='R';
            printf("\nP%d��������.......\n",run->pid);
            //printf("���н���:\n");
            //DisplayPCB(run);
            if(run->rest == 0)
            {
                printf("\nP%d����!\n",run->pid);
                run->state = 'T';
                run->next = finish;   //����ɵĽڵ���뵽finish��ͷ���,��һ��
                finish = run;
                run = NULL;
                printf("�������̶���:\n");
                DisplayPCB(finish);
            }
        }
        timenow++; //��һʱ�̼���ɨ����ҵ����
    }
}
int main()
{
    srand((int)time(NULL)); //���������
    InitialJob();
    DisplayPCB(job->next);
    int s = 1;
    printf("Please type the Algorithm(Priority\\Round Robin):");
    scanf("%d",&s);
    if (s  ==  1)
    {
        Priority();//��������
    }
    else
    {
        RR();//����ת��
    }
    printf("SYSTEM FINISHED\n");
    return 0;
}
