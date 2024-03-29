//
// Created by 樊玲君 on 2019/10/22.
//
/**
 *
在n个银币中有一个是不合格的，不合格的银币比合格银币要轻。
现用天平秤银币，找出不合格的银币，且在最坏情况下秤银币的次数最少。

输入
输入有若干行。每行上有一个整数n，表示银币个数，n<=100000。

当n=0，表示输入结束。

输出
对输入大于0的整数n，输出2行。第1行输出n的值，第2行上先输出“Times:”，接着输出在最坏情况下秤n个银币的最少次数。

当n=0时，这种情况你不必处理和结果输出。

input
4
7
50
0

4
Times:2
7
Times:2
50
Times:4

 *
 *
 *
 * **/

#include <iostream>
using namespace std;

// 我们可以考虑分成3堆
// 13 = 4 4 5
// 14 = 5 5 3

int Calculate(int n)
{
    int sum = 0,x1,x2,x3;

    while (n != 1&&n != 0)
    {
        if ((n + 1) % 3 == 0)
        {
            x1 = x2 = (n + 1)/3;
            x3 = x1 - 1;
            n = x1;
        }
        else if ((n - 1) % 3 == 0)
        {
            x1 = x2 = (n - 1)/3;
            x3 = x1 + 1;
            n = x3;
        }
        else
            n = x1 = x2 = x3 = n/3;

        //n = x1; // 我们总是假设假币在两堆之中
        sum++;
    }

    return sum;
}


int main()
{
    int n;
    while (1)
    {
        cin>>n;
        if (n == 0) exit(0);
        int re;
        re = Calculate(n);
        cout<<"Times: "<<re<<endl;
    }
}
