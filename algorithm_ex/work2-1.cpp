//
// Created by 樊玲君 on 2019/10/20.
//

#include <iostream>
using namespace std;
#define N 1000
/**
        众数问题
 **/

int main()
{
    int num,x;
    int array[N] = {0};
    int max = -1;
    int max_frequency = -1;
    cin>>num;
    for (int i = 0;i < num;i++)
    {
        cin>>x;
        array[x]++;
        if (array[x] > max_frequency)
        {
            max_frequency = array[x];
            max = x;
        }
    }

    cout<<max<<endl;
    cout<<max_frequency<<endl;
}