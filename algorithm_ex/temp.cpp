//
// Created by 樊玲君 on 2019/10/9.
//

/*

#include<iostream>
#include<string>
#include<cstring>
#include<string.h>
#include<stdlib.h>
using namespace std;

typedef struct {
    string item;
    void init(int x)
    {
        char c;
        itoa(x,&c,10);
        string a = "A";
        this->item = a + c;
        cout<<"i am "<<this -> item<<"\t";
    }
    void show_item()
    {
        cout<<this -> item;
    }
}Str_item;
typedef struct {

    Str_item *item;
    int size;
    int cur; // 当前

}Item_list;
Creat_list(Item_list *i)
{
    int n = 5;
    i -> item = new Str_item();
    for (int j = 1;j <= 5;j++)
    {
        (i -> item[j - 1]).init(j);
    //(this -> item[i - 1]).show_item();
    }
    i -> size = n;
    i -> cur = 0;
}
void test()
{
    cout<<"hi "<<endl;
}
void Show(Item_list *i)
{
    cout<<"Test "<<endl;
    cout<<i ->size<<endl;
    for (int j = 0;j < i ->size;j++)
    {
        cout<<"test "<<endl;
        (i -> item[j]).show_item();
    }
}

int main()
{

    Item_list it;
    Creat_list(&it);
    Show(&it);
}


*/

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

vector<string> vec(10);
// 利用array存储这个半数集
int array[100] = {0};


/*char *ToChar(int a)
{
    char *c;
    c = a + 48;
    return c;
}*/

int main()
{
    int n = 6;
    string str = to_string(n);
    string str_1 = "444";
    cout<<stoi(str_1);
    cout<<atoi(str_1[2].c_str(q));
    /*vec[0] = str;
    cout<<vec[0]<<endl;
    str_1.append(str);
    vec[1] = str_1;
    cout<<vec[1]<<endl;*/

    return 0;
}