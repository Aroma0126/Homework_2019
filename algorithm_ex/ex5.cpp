//
// Created by 樊玲君 on 2019/10/20.
//
/**Dijstra**/

#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>

// 定义一个很大的数
#define Inf 0x3f3f3f3f

using namespace std;

int map[1005][1005];

int vis[1005],dis[1005];
int path[500];
int n = 6 ,m = 0; // n个点，m条边

void Getmap()
{
    int u,v,w;

    int x;
    for (int i = 1;i <= n;i++)
    {
        for (int j  = 1;j <= n;j++)
        {
            cin>>x;
            if (i != j)
            {
                if (x > 0)
                {
                    m++;
                    map[i][j] = x;
                }
                else {
                    map[i][j] = Inf;
                }
            }

        }
    }

}

void Dijkstra(int u)
{
    memset(vis,0,sizeof(vis));
    for(int t = 1;t <= n;t++)
    {
        dis[t] = map[u][t];
        vis[t] = 0;
        path[t] = u;
    }
    vis[u] = 1;
    for(int t = 1;t < n;t++)
    {
        int minn = Inf,temp;
        for(int i = 1;i <= n;i++)
        {
            if(!vis[i]&&dis[i] < minn)
            {
                minn = dis[i];
                temp = i;
            }
        }
        vis[temp] = 1;
        for(int i = 1;i <= n;i++)
        {
            if(vis[i] == 0&&map[temp][i] + dis[temp] < dis[i])
            {
                dis[i] = map[temp][i] + dis[temp];
                path[i] = temp;
            }
        }
    }

}

int main()
{
    int cnt = 1;
    while (cin>>n)
    {
        int start = 1,end = 6;
        memset(map,Inf,sizeof(map));
        for(int i = 1;i <= n;i++)
        {
            map[i][i] = 0;
        }
        Getmap();
        cin>>start>>end;
        Dijkstra(start);

        cout<<"Case "<<cnt<<":"<<endl;
        cout<<"The least distance from "<<start<<"->"<<end<<" is "<<dis[end]<<endl;

        int p[500],k = 0,temp = end; //输出路径
        while(temp != start)
        {
            p[k++] = temp;  //一开始p[0] = 终点
            temp = path[temp]; //倒着来 推向temp的
        }
        p[k] = start;
        cout<<"the path is ";
        for(int i = k;i > 0;i--)
            cout<<p[i]<<"-->";
        cout<<p[0]<<endl;
        cnt++;
    }

    /*for (int i = 1;i <= 6;i++)
        cout<<dis[i]<<"\t";*/

    return 0;
}


/**


 6
-1 1 12 -1 -1 -1
-1 -1 9 3 -1 -1
-1 -1 -1 -1 5 -1
-1 -1 4 -1 13 13
-1 -1 -1 -1 -1 4
-1 -1 -1 -1 -1 -1
1 6


5
-1 10  -1 30 100
-1 -1 50 -1  -1
-1 -1 -1 -1 10
-1 -1 20 -1 60
-1 -1 -1 -1 -1
1 5


 **/