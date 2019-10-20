//
// Created by 樊玲君 on 2019/10/15.
//
/**循环赛**/

#include <iostream>
#include <math.h>
using namespace std;
#define N 50

// 定义一个二维数组，用列表示当前赛到第几天

void table(int k)
{
    /**
     * n:运动员个数
     *
     * **/

    int a[N][N];
    a[1][1] = 100;
    int n = pow(2,k);
    /**填充这个表的第一行**/
    for (int i = 1;i <= n;i++)
        a[1][i] = i;

    int m = 1; /** m用来控制每一次填表时i行j列的起始填充位置 **/
    /**s指分成几大步进行制作日程表**/
    for (int s = 1;s <= k;s++)
    {
        n = n/2;
        for (int t = 1;t <= n;t++) /** t指明内部对称赋值的循环次数 **/
            for (int i = m + 1;i <= 2 * m;i++)
                for (int j = m + 1;j <= 2 * m;j++)
                {
                    a[i][j + (t - 1)*m*2] = a[i - m][j + (t - 1)*m*2 - m];/**右下角等于左上角**/
                    a[i][j + (t - 1)*m*2 - m] = a[i - m][j + (t - 1)*m*2];/**左下角等于右上角**/
                }
        m = m * 2;
    }
    n = pow(2,k);// 这时候n变小了，当然只打印一点点了！！！！！！！！
    cout<<"----------------------------------------------------------"<<endl;
    for (int i = 1;i <= n;i++)
    {
        cout<<"NO."<<i<<":"<<"\t|";
        for (int j = 2;j <= n;j++)
            cout<<a[i][j]<<"\t";
        cout<<endl;
    }
    cout<<"----------------------------------------------------------"<<endl;
}

int main()
{
    int k = 3;
    //cin>>k;
    /*int n = pow(2,k);
    int *a[n + 1];
    for(int i = 1;i <= n + 1;i++)   //给每行的数组分配一下空间
    {
        a[i]=new int [n + 1];
    }*/
    table(k);

}