//
// Created by 樊玲君 on 2019/10/15.
//
// 太难了！！！！！！！！！！
/**
设子数组a[0:k-1]和a[k:n-1]已排好序$(0\leqslant k \leqslant n-1)$。
 试设计一个合并这两个子数组为排好序的数组a[0:n-1]$算法。要求算法在最坏情况
 下所用的计算时间为O(n)，且只用到O(1)的辅助空间。
 **/

#include <iostream>
using namespace std;

/** 假设数组被k分为A,B两部分，结果放在B部分的末尾，将结果区域记为C
 * 则将AB中较小的数与B的头部交换，再将B的头部与B的尾部交换，并将B的头部后移一位，“空出”的A与B之间的部分记为D
 * 则当B与结果区域C碰头的时候，结果区域C其实是全局有序的
 * 而碰头时，“空出”的D部分其实是C一直向前推，占据的B的尾部区域那些数的逆序排列
 * A区域的头部一直没变
 * 所以需要判断A区域和D区域（逆序向前推）谁更小，交换到D区域，作为结果区域C的补充
 * 这样就会将B区域部分完全转化为结果区域C
 * 而A部分又分割成了相同的子问题，此时k值为之前“空出”的D部分的长度

 */

void show(int arr[])
{
    for (int i = 0;i < 10;i++)
        cout<<arr[i]<<"\t";
    cout<<endl;
}

void mergeArr(int arr[], int n, int k) {
    int i = 0, j = k, cnt = 0;
    while (i < k && j < n - cnt) {
        if (arr[i] < arr[j]) {
            swap(arr[i], arr[j]);
            swap(arr[n - cnt - 1], arr[j++]);
        } else {
            swap(arr[n - cnt - 1], arr[j++]);
        }
        cnt++;
        show(arr);
    }
    for (int l = n - cnt - 1; l >= k; --l) {
        if (arr[i] < arr[l]) {
            swap(arr[i++], arr[l]);
        }
    }
    if (i < k)mergeArr(arr, k, i);
}



int main()
{
    int array[10] = {0,5,9,10,20,1,2,3,4,5};
    //int array[10] = {1, 5, 7, 8, 12, 2, 3, 4, 6, 9};
    mergeArr(array,10,5);
    cout<<endl;
    show(array);
}