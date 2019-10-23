//
// Created by 樊玲君 on 2019/10/22.
//

/**独立任务最优调度问题**/

#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;
/**
 * 6
 * 2 5 7 10 5 2
 * 3 8 4 11 3 4
 * 0 1 2 3  4 5
 *
 * 15 ---> 0 5 1 3 2 4
 * -- -- -----
 * --- ---- --------
 * **/
// N1 = {0,1,3,5}
// sort_to_max(N1) -----> {0,5,1,3}
// N2 = {2,4}
// sort_to_min(N2) -----> {2,4}
// marge(N1,N2)


/**
 * 流水作业调度的Johnson算法
 *
 *
 * **/

int Johnson(int a[],int b[],int n)
{
    vector<int> N1,N2;
    for (int i  = 0;i < n;i++)
    {
        if (a[i] < b[i])
            N1.push_back(i);
        else N2.push_back(i);
    }
    // 正向排序：按照从小到大的顺序排序
    sort(N1.begin(), N1.end());
    // 逆向排序：按照从大到小的顺序排序
    sort(N2.rbegin(), N2.rend());
    // merge 2 vector
    N1.insert(N1.end(),N2.begin(),N2.end());

    int sum = 0;
    int blank_1,blank_2;
    blank_1 = blank_2 = 0;
    for (int i = 0;i < n;i++)
    {
        int pos = N1[i];
        a[pos] = a[pos] - blank_1;
        b[pos] = b[pos] - blank_2;
        if (a[pos] < b[pos]) {
            sum = sum + b[pos];
            blank_1 = b[pos] - a[pos];
        }
        else
        {
            sum = sum + a[pos];
            blank_1 = a[pos] - b[pos];
        }
    }
    return sum;
}



int main()
{
    int n;
    cin>>n;
    int a[n],b[n];

    for (int i = 0;i < n;i++)
        cin>>a[i];
    for (int i = 0;i < n;i++)
        cin>>b[i];

    cout<<Johnson(a,b,n)<<endl;

    return 0;
}