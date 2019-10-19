//
// Created by 樊玲君 on 2019/10/15.
//
/**循环赛**/

#include <iostream>
#include <math.h>
using namespace std;

// 定义一个二维数组，用列表示当前赛到第几天

void table(int k,int **a)
{
    /**
     * n:运动员个数
     *
     * **/
    int n = 1;
    for (int i = 1;i <= k;i++)
        n = n * 2;
    for (int i = 1;i <= n;i++)
        a[1][i] = i;

    int m = 1;
    for (int s = 1;s <= k;s++)
    {
        n = n/2;
        for (int t = 1;t <= n;t++)
            for (int i = m + 1;i <= 2 * m;i++)
                for (int j = m + 1;j <= 2 * m;j++)
                {
                    a[i][j + (t - 1)*m*2] = a[i - m][j + (t - 1)*m*2 - m];
                    a[i][j + (t - 1)*m*2 - m] = a[i - m][j + (t - 1)*m*2];
                }
        m = m * 2;
    }

    for (int i = 1;i <= n;i++)
    {
        cout<<"NO."<<i<<": ";
        for (int j = 1;j <= n;j++)
            cout<<a[i][j]<<"\t";
        cout<<endl;
    }
}

int main()
{
    int k = 3;
    //cin>>k;
    int n = pow(2,k);

    int *a[n];
    for(int i = 0;i < n;i++)   //给每行的数组分配一下空间
    {
        a[i]=new int [n];
    }
    table(k,(int **)a);

}