//
// Created by 樊玲君 on 2019/10/9.
//

// 最长子序列问题

#include <iostream>
#include <string>
#include <string.h>
#include <cstring>
using namespace std;

void Lcs_length(int m,int n,string &x,string &y,int **c,int **b)
{
    int i;
    int j;
    for (i = 1;i <= m;i++)
        c[i][0] = 0;
    for (i = 1;i <= n;i++)
        c[0][i] = 0;
    for (i = 1;i <= m;i++)
        for (j = 1;j <= n;j++)
        {
            if (x[i] == y[j])
            {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 1;
            }
            else if (c[i - 1][j] >= c[i][j - 1])
            {
                c[i][j] = c[i - 1][j];
                b[i][j] = 2;
            }
            else
            {
                c[i][j] = c[i][j - 1];
                b[i][j] = 3;
            }

        }
}

void Lcs(int i,int j,string &x,int **b)
{
    if (i == 0||j == 0)
        return;
    if (b[i][j] == 1)
    {
        Lcs(i - 1,j - 1,x,b);
        cout<<x[i];
    }
    else if (b[i][j] == 2)
    {
        Lcs(i - 1,j,x,b);
    }
    else
    {
        Lcs(i,j - 1,x,b);
    }


}

int main()
{
    int m,n,number;
    string x,y;
    //cin>>number;
    number = 1;

    for (int i = 0;i < number;i++)
    {

        cin>>m;
        cin>>n;
        cin>>x;
        cin>>y;
        //x = &a;
        //y = &b;
        int max = m > n?m : n;
        int *c[max],*b[max];
        for(int i = 0;i < max;i++)   //给每行的数组分配一下空间
        {
            c[i]=new int [max];
            b[i]=new int [max];
        }

        Lcs_length(m,n,x,y,c,b);
        Lcs(m,n,x,b);

    }

}

/*
 *


7
6
abcbdab
bdcaba





 */
