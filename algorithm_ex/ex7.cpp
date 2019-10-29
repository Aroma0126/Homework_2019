//
// Created by 樊玲君 on 2019/10/21.
//
/**装载问题**/

#include <iostream>
using namespace std;

int n; // 集装箱的个数
int cur_weight; // 当前载重量
int best_weight; // 最优载重量
int rest_weight; // 剩余集装箱的重量
int c1,c2;
int x[100];
int best_x[100]; // 最优
int weight[100];

void BackTrack(int i)

{
    // 到达叶结点
    if (i > n)
    {
        if (cur_weight > best_weight)
        {
            for (int i = 1;i <= n;i++)
                best_x[i] = x[i];
            best_weight = cur_weight;
        }
        return;
    }
    // 搜索子树
    rest_weight = rest_weight - weight[i];
    // 搜索左子树
    if (cur_weight + weight[i] <= c1)
    {
        cur_weight = cur_weight + weight[i];
        x[i] = 1;
        BackTrack(i + 1);
        x[i] = 0;
        cur_weight = cur_weight - weight[i];
    }
    // 搜索右子树
    if (cur_weight + rest_weight > best_weight)
    {
        x[i] = 0;
        BackTrack(i + 1);
    }
    // 回溯
    rest_weight = rest_weight + weight[i];
}

int main()
{
    int cnt = 1;
    while (cin>>n)
    {
        best_weight = rest_weight = cur_weight = 0;
        for (int i = 1;i <= n;i++)
        {
            cin>>weight[i];
            rest_weight = rest_weight + weight[i];
        }
        cin>>c1>>c2;
        BackTrack(1);
        cout<<"Case "<<cnt<<":"<<endl;
        int restweight = 0;
        for (int i = 1;i <= n;i++)
        {
            if (best_x[i] == 0)
                restweight = restweight + weight[i];
        }
        if (restweight > c2)
            cout<<"no!"<<endl;
        else
        {
            cout<<best_weight<<" ";
            for (int i = 1;i <= n;i++)
                cout<<best_x[i]<<" ";
            cout<<endl;
        }

        cnt++;
    }
}
/**
3
10 40 40
50 50

3
20 40 40
50 50

 **/