//
// Created by 樊玲君 on 2019/10/21.
//

/**半数集问题**/
/**
 * 写在前面：花费我的时间和精力的是对于string和int间的转换
 * 以及使用vector容器的坑！！！
 * 总而言之，要转string就直接用to_string
 * 转回数字就用这个字符减去‘0’
 * 还有在给一个string类型赋值的时候不要打单引号！！！！！那表示字符！！
 * 总之会报错的
 *
 * 本来很简单，搞不清楚就很难！！！
 *
 * **/

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

vector<string> vec;

void get_set(string s)
{

    int first = s[0] - '0';
    int max = first/2;

    for (int i = 1;i <= max;i++)
    {
        string c;
        c = to_string(i);
        c.append(s); // 拼接
        vec.push_back(c);
        // 赋值,坑死了，vector默认追尾，假如说设
        // 置了100长度的vector默认从101开始追加！！！！！
        get_set(c); //
    }

}


int main()
{
    int n;
    while (cin>>n)
    {
        string str = to_string(n);
        vec.push_back(str);
        get_set(str);
        cout<<"the sum of set is: "<<vec.size()<<endl;
        for (int i = 0;i < vec.size();i++)
            cout<<vec[i]<<"\t";
        cout<<endl;
        vec.clear();
    }

    return 0;
}