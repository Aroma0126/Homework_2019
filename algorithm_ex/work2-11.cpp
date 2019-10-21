//
// Created by 樊玲君 on 2019/10/21.
//
/**整数因子分解问题**/

#include <iostream>
using namespace std;

int get_num(int n)
{
    // 首先考虑一种情况，任何一个数字等于它乘它自己
    int a = n,b = 1;
    int sum = 1;
    // if n 为偶数
    // if n 为奇数
    for (int i = b + 1;i <= (n/2);i++)
    {
        // 首先能整除
        if (n % i == 0)
        {
            a = n / i;
            sum = sum + get_num(a);
        }

    }
    return sum;

}


int main()
{
    int n,cnt = 1;
    while (cin>>n)
    {
        int result = get_num(n);
        cout<<"Case "<<cnt<<": ";
        cout<<result<<endl;
        cnt++;
    }
    return 0;
}
