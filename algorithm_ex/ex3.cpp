//
// Created by 樊玲君 on 2019/10/9.
//

// 最长子序列问题


#include <iostream>
#include <string>
#include <string.h>
#include <cstring>
#include <algorithm>
using namespace std;

void Lcs_length(int m,int n,string x,string y,int **c,int **b)
{

/**
     * c 存储  X_i   Y_j   的最长公共子序列的长度
     * b 记录c的值是由哪个子问题的解而得到的。这对于构造序列的时候起作用
     *
     *
     * **/

    int i;
    int j;
    for (i = 0;i < m + 1;i++)
        c[i][0] = 0;
    for (i = 0;i < n + 1;i++)
        c[0][i] = 0;
    for (i = 1;i < m + 1;i++)
    {
        for (j = 1;j < n + 1;j++)
        {
            if (x[i - 1] == y[j - 1])
            { // 相等的情况 记为第一类
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 1;
            }
            else if (c[i - 1][j] >= c[i][j - 1])
            { // 不相等的情况，填大的那一个数字 记为第二类
                c[i][j] = c[i - 1][j];
                b[i][j] = 2;
            }
            else
            { // 不相等的情况，填小的那一个数字 记为第三类
                c[i][j] = c[i][j - 1];
                b[i][j] = 3;
            }
        }

    }

    for (i = 0;i < m + 1;i++)
    {
        for (j = 0;j < n + 1;j++)
            cout<<b[i][j]<<"\t";
        cout<<endl;
    }
    cout<<endl;
    for (i = 0;i < m + 1;i++)
    {
        for (j = 0;j < n + 1;j++)
            cout<<c[i][j]<<"\t";
        cout<<endl;
    }

}


int main()
{
    int m,n,number;
    cin>>number;

    string x,y;

    for (int no = 0;no < number;no++)
    {

        cin>>m;
        cin>>n;
        cin>>x;
        cin>>y;

        int **c;
        int **b;
        c = new int* [m + 1];
        b = new int* [m + 1];
        for(int i = 0;i <= m + 1;i++)
        {
            c[i] = new int [n + 1];
            b[i] = new int [n + 1];
            for(int j = 0;j <= n + 1;j++)
                b[i][j] = 0;
        }





        Lcs_length(m,n,x,y,c,b);
        //LCS(m + 1,n + 1,x,b);

        string re;
        for(int i = m,j = n;i >= 0 && j >= 0; )
        {
            if(b[i][j] == 1)
            {
                i--;
                j--;
                //cout<<x[i]<<" ";
                re = re + x[i];
            }
            else if(b[i][j] == 2)
                i--;
            else
                j--;
        }

        reverse(re.begin(),re.end());
        cout<<"Case "<< no + 1 << endl;
        cout<<c[m][n]<<" "<<"LCS(X,Y): "<<re<<endl;

        for(int k = 0;k < m + 1;k++)
        {
            delete [] c[k];
            delete [] b[k];
        }

        delete [] c;
        delete [] b;
    }

}
/**

2
7 6
ABCBDAB
BDCABA
8 9
baababab
ababbabba





 **/