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

// 2 4 6 8 10 12 13 14 14 17
// 0 1 2 3 4  5  6  7  8  9

void MyBinarySearch (int key, int array[], int n)
{
    int i,j;
    int l = 0, r = n - 1, mid = -1;
    while (l < r) {
        mid = (l + r) / 2;
        if (key == array[mid]) {
            i = j = mid;
            cout<<"i = j = "<<i<<endl;
            return;
        } else if (key < array[mid]) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    //找不到元素,从mid-1开始向高index找符合条件的解
    for (--mid; mid + 1 < n && array[mid + 1] < key; ++mid);
    i = mid;
    j = ++mid;
    cout<<"i = "<<i<<"j = "<<j<<endl;
}


int main()
{
    int n;
    cout<<"input the size of array:";
    cin>>n;
    int array[10000];
    cout<<"input the array:"<<endl;
    for (int i = 0;i < n;i++)
        cin>>array[i];
    int x;
    cout<<"input x: ";

    while(cin>>x)
    {
        MyBinarySearch(x,array,n);
        cout<<"input x: ";
    }

}
/**
10
2 4 6 8 10 12 13 14 14 17
3
 **/