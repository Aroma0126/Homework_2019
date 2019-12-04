#include <cstdio>
#include <ctime>
#include <cstring>
#include <cstdlib>
const long n=5;

struct pcbtype		//进程控制块结构
{
    long id, priority, runtime, totaltime;
    char status;	//R, W, F -> 运行，就绪，完成
}PCB[n+1];

long link[n+1];	//链表结构
long RUN, HEAD, TAIL;
//选择算法
long ChooseAlgo()
{
    char s[128];
    printf("Please type the Algorithm(Priority\\Round Robin):");
    gets(s);
    if (s[0]=='P' || s[0]=='p')
        return 1;
    return 0;
}
//初始化
void init()
{
    long i;
    for (i=1; i<=n; i++)
    {
        PCB[i].id = i;
        PCB[i].priority = rand()%4+1;
        PCB[i].runtime = 0;
        PCB[i].totaltime = rand()%8+1;
        PCB[i].status = 'W';
    }
}
//显示进程调度状况
void showit()
{
    long i;
    printf("=====================================================\n");
    printf("%-25s","ID");
    for (i=1; i<=n; i++)  printf("%4ld", PCB[i].id);
    printf("\n%-25s","PRIORITY//TURNTIME");
    for (i=1; i<=n; i++)  printf("%4ld", PCB[i].priority);
    printf("\n%-25s", "CPUTIME");
    for (i=1; i<=n; i++)  printf("%4ld", PCB[i].runtime);
    printf("\n%-25s", "ALLTIME");
    for (i=1; i<=n; i++)  printf("%4ld", PCB[i].totaltime);
    printf("\n%-25s","STATUS");
    for (i=1; i<=n; i++)  printf("%4c", PCB[i].status);
    printf("\n=====================================================\n");
    if (RUN != -1)  printf("RUNNING PROCESS: %ld\n", RUN);
    else printf("RUNNING PROCESS: NULL\n");
    printf("WAITING QUEUE: ");
    for (i=HEAD; i!=-1; i=link[i])  printf("%ld ", i);
    printf("\n\n");
}
//优先数调度算法
void main_priority()
{
    long i, j, k;
    long sort[n+1];
    init();
//设置就绪链
    for (i=1; i<=n; i++)
    {
        sort[i] = i;
    }
    for (i=1; i<=n; i++)		 //根据优先数排序
    {
        for (j=n; j>i; j--)
        {
            if (PCB[sort[j]].priority > PCB[sort[j-1]].priority)
            {
                k=sort[j]; sort[j]=sort[j-1]; sort[j-1]=k;
            }
        }
    }

    HEAD=sort[1];
    for (i=1; i<n; i++)
    {
        link[sort[i]] = sort[i+1];
    }
    TAIL = sort[n];
    link[TAIL] = -1;
    RUN = -1;
    //就绪链设置完毕
    RUN = HEAD;
    PCB[RUN].status = 'R';
    HEAD = link[HEAD];		//运行链首进程
    while (RUN != -1)
    {
        showit();
        PCB[RUN].totaltime--;
        PCB[RUN].priority -= 3;     //优先级减3
        PCB[RUN].runtime++;
        if (PCB[RUN].totaltime == 0)	//进程运行完成
        {
            PCB[RUN].status='F';
            RUN = HEAD;
            if (HEAD != -1)
                HEAD = link[HEAD];
            PCB[RUN].status='R';
        }
        else
        {
            if (HEAD != -1 && PCB[RUN].priority < PCB[HEAD].priority)
            {
                k=HEAD;
                PCB[RUN].status = 'W';
                //寻找等待链中的合适位置
                while (k!=TAIL && PCB[link[k]].priority > PCB[RUN].priority)
                    k=link[k];
                if (k == TAIL)
                {
                    link[k] = RUN;		//插入链尾之后
                    TAIL = RUN;
                    link[RUN] = -1;
                    RUN = HEAD;
                    HEAD = link[HEAD];
                    PCB[RUN].status = 'R';
                }
                else
                {
                    link[RUN] = link[k];		//插入链中
                    link[k] = RUN;
                    RUN = HEAD;		//链首进程开始运行
                    HEAD = link[HEAD];
                    PCB[RUN].status = 'R';
                }
            }
        }
    }
    showit();
}
//轮转调度算法
void main_round_robin()
{
    long i;
    init();
    //设置就绪链
    HEAD = 1;
    for (i=1; i<n; i++)
    {
        link[i] = i+1;
    }
    TAIL = n;
    link[TAIL] = -1;
    RUN = -1;
    //就绪链设置完毕
    RUN = HEAD;
    PCB[RUN].status = 'R';
    HEAD = link[HEAD];//运行首进程
    while (RUN != -1)
    {
        showit();
        PCB[RUN].totaltime--;
        PCB[RUN].runtime++;
        if (PCB[RUN].totaltime == 0)//进程运行完成
        {
            PCB[RUN].status = 'F';
            RUN = HEAD;
            if (HEAD != -1)
                HEAD = link[HEAD];
            PCB[RUN].status = 'R';
        }
        else
        {
            if (HEAD != -1 && PCB[RUN].runtime % PCB[RUN].priority==0)//轮转时间到
            {
                PCB[RUN].status='W';	//插入链尾
                link[TAIL]=RUN;
                link[RUN]=-1;
                TAIL=RUN;
                RUN=HEAD;//链首进程开始运行
                HEAD=link[HEAD];
                PCB[RUN].status='R';
            }
        }
    }
    showit();
}
//主函数
int main()
{
    long algo;
    srand(time(NULL));
    algo = ChooseAlgo();
    if (algo == 1)
    {
        main_priority();//优先数法
    }
    else
    {
        main_round_robin();//简单轮转法
    }
    printf("SYSTEM FINISHED\n");
    return 0;
}
