//
// Created by 樊玲君 on 2019/10/21.
//

/**双色汉诺塔问题**/
/**注意：题目要求的是字母**/
#include <iostream>
using namespace std;

void Move(int n,char x,char y)
{
    cout<<n<<" "<<x<<" "<<y<<endl;
}

void Hanoi(int n,char a,int b,int c)
{
    if (n > 0)
    {
        Hanoi(n - 1,a,c,b);
        Move(n,a,b);
        Hanoi(n - 1,c,b,a);
    }
}

int main()
{
    int n;
    while (cin>>n)
    {
        Hanoi(n,'A','B','C');
    }
    return 0;
}