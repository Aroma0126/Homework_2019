//
// Created by 樊玲君 on 2019/9/29.
//
/** 2-3
 * 设a[0:n-1]是已排好序的数组.请改写二分搜索算法,使得当搜索元素x不在
 * 数组中时,返回小于x的最大元素位置i和大于x的最小元素位置j.当搜索元素
 * 在数组中时,i和j相同,均为x在数组中的位置.
**/
#include <iostream>
using namespace std;

// 2 4 6 8 10
// 0 1 2 3 4

void MyBinarySearch(int a[],int left,int right,int &x)
{
    // i,j 两个位置 定义为-1就是没找到的意思
    int i,j;
    int mid = (left + right)/2;
    if ((right - left) == 1) // 只剩下一个元素了
    {
        if (x == a[left])
            i = j = left;
        else if (x == a[right])
            i = j = right;
        else if ((x < a[right])&&(x > a[left]))
        {
            i = left;
            j = right;
        }
        else if (x < a[left])
        {
            i = -1;
            j = left;
        }
        else if (x > a[right])
        {
            i = right;
            j = -1;
        }
        cout<<"i = "<<i<<" j = "<<j<<endl;
    }
    else
    {
        if (x == a[mid])
        {
            i = j = mid;
            cout<<"i = "<<i<<" j = "<<j<<endl;
        }
        else if (x < a[mid])
        {
            MyBinarySearch(a,left,mid,x);
        }
        else
        {
            MyBinarySearch(a,mid + 1,right,x);
        }
    }
}


int main()
{
    int a[12];
    a[0] = 0;
    for (int i = 1;i < 12;i++)
    {
        a[i] = a[i - 1] + 2;
        cout<<"a["<<i<<"] "<<a[i]<<" ";
    }

    int x1 = -3;  // situation 1
    int x2 = 3;   // situation 2
    MyBinarySearch(a,0,8,x2);
}