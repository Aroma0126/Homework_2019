//
// Created by 樊玲君 on 2019/9/5.
//
// 矩阵连乘问题——动态规划


#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
using namespace std;

void MatrixChain(int *p,int n,int **m,int **s)
{
    /**
     * p:所有矩阵的维数 比如 A(3x4) B(4x6) C(6x9) 那么p = [3,4,6,9]
     * n:矩阵个数
     * m:最少相乘次数 m[1][1] m[2][2] m[3][3] m[1][2] m[2][3]
     * s:最优断开位置
    **/
    // 只有一个矩阵的情况
    for (int i = 1;i <= n;i++)
        m[i][i] = 0;
    //分别计算矩阵链长度(r)逐渐递增的情况
    for (int r = 2;r <= n;r++)
    {
        for (int i = 1;i <= (n - r + 1);i++)
        {
            int j = i + r - 1;// 用来计算指定长度下的坐标，比如长度为2那么计算m[1][2] m[2][3] m[3][4]
                              // 长度为3计算m[1][3] m[2][4]
            m[i][j] = m[i + 1][j] + p[i - 1]*p[i]*p[j];
            s[i][j] = i;// 暂时最优断开位置
            for (int k = i + 1;k < j;k++)
            {
                int t = m[i][k] + m[k + 1][j] + p[i - 1]*p[k]*p[j];
                if (t < m[i][j])
                {
                    m[i][j] = t;// 改变最少相乘次数
                    s[i][j] = k;// 改变最优断开位置
                }
            }
        }

    }

}


void Print(int i,int j,int **s)
{
    if(i == j)
    {
        cout<<"A"<<i<<"";
        return;
    }
    cout<<"(";
    Print(i,s[i][j],s);
    Print(s[i][j]+1,j,s);
    cout<<")";
}



int main()
{
    int nn,n,x;
    int cnt = 1;
    while (cin>>nn)
    {
        n = nn + 1;
        int p[n];
        for (int i = 0;i < n;i++)
        {
            cin>>x;
            p[i] = x;
        }

        // https://www.cnblogs.com/chenhanwu/p/9897461.html
        int *m[n],*s[n];
        for(int i = 0;i < n;i++)   //给每行的数组分配一下空间
        {
            m[i]=new int [n];
            s[i]=new int [n];
        }
        for (int ii = 0;ii < n;ii++)
        {
            for (int jj = 0;jj < n;jj++)
                m[ii][jj] = -1;
        }

        MatrixChain(p,nn,(int **)m,(int **)s);
        cout<<"Case #"<<cnt<<" ";
        cout<<m[1][nn]<<"\t";
        Print(1,nn,(int **)s);
        cnt++;
        cout<<endl;
    }
    return 0;
}