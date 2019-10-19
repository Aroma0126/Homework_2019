//
// Created by 樊玲君 on 2019/9/29.
//

/** 2-8
 *设a[0:n-1]是有n个元素的数组，k是一个非负整数。
 * 试设计一个算法将子数组a[0:k-1]与a[k:n-1]换位。要
 * 求算法在最坏情况下所用的计算时间为O(n)，且只用到
 * O(1)的辅助空间。
**/

#include <iostream>
using namespace std;

void swap_sub_buffer(int a[],int k)
{
    int temp;
    for(int i = 0;i < k;i++)
    {
        temp = a[i];
        a[i] = a[i + k];
        a[i + k] = temp;
    }

    for(int i = 0;i < 10;i++)
        cout<<a[i]<<" ";
}

int main()
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    int k = 5;
    swap_sub_buffer(a,k);
}


