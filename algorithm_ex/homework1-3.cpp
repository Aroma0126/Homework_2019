//
// Created by 樊玲君 on 2019/9/8.
//

#include <iostream>

using namespace std;

int div(int n)
{
    int x = 0;
    for (int i = 2;i <= n;i++)
    {
        if (n % i == 0)
            x++;
    }
    return x + 1;
}

int main()
{
    int a,b;
    cin>>a>>b;
    int max = -1,max_num = a;
    for (int i = a;i <= b;i++)
    {
        if (div(i) > max)
        {
            max = div(i);
            max_num = i;
        }
    }
    cout<<max;
}

