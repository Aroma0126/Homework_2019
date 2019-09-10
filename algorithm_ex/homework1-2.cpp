//
// Created by 樊玲君 on 2019/9/8.
//

#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

int f(int i,int k)
{
    // 第i个字母开头，长度为k的数量
    // 比如i = 2,k = 2,则合适的情况有：bc,bd,be,bf.....bz一共23个
    int sum = 0;
    if (k == 1)
        return 1;
    else
    {
        for (int j = i + 1;j <= 26;j++)
        {// 从当前字母的下一个开始组合，
            sum += f(j,k - 1);
        }
    }
    return sum;
}

int calculate(char s[])
{

    int sum = 0;
    int length = strlen(s);
    // 首先计算小于length长度的数量，比如length = 3，则先算1位的和2位的
    for (int i = 1;i < length;i++)// 位数
        for (int j = 1;j <= 26;j++)
        {
            sum += f(j,i);
        }

    // 现在计算长度为length,但是小于开头字母的数量
    // 比如length = 3,第一个字母是d,那么我们计算开头字母是a/b/c的长度为3的字符串
    int first_letter = s[0] - 'a' + 1;
    for (int i = 1;i < first_letter;i++)
        sum += f(i,length);


    // 最后计算s中的第i个字母与其后面字母开头的s - i长度的数量
    // 比如s = 3,i = 2，第二个字母为f,那么我们考虑ga,gb.gc...ha,hb,hc...
    int num = first_letter;
    for (int i = 1;i < length;i++)
    {
        int n = s[i] - 'a' + 1;
        int sub_length = length - i;
        for (int j = num + 1;j < n;j++)
            sum += f(j,sub_length);
        num = n;
    }

    return sum + 1;
}

int main()
{
    int n;
    cin>>n;
    char s[6];
    while (n--)
    {
        cin>>s;
        cout<<calculate(s)<<endl;
    }
}
