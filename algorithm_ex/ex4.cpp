//
// Created by 樊玲君 on 2019/10/19.
//
/**huffman code**/

#include <iostream>
using namespace std;


typedef struct Haffman
{
    int weight;
    char ch;
    int parent;
    int leftChild;
    int rightChild;
}HaffmaNode;

typedef struct Code
{
    int code[100]; // 字符的哈夫曼编码的存储
    int start; // 从哪个位置开始
}HaffmaCode;

HaffmaNode haffman[100];
HaffmaCode code[100];

void buildHaffman(int n)
{

    //哈夫曼节点的初始化之前的工作, weight为0,parent,leftChile,rightChile都为-1
    for (int i = 0; i < n * 2 - 1; ++i)
    {
        haffman[i].weight = 0;
        haffman[i].parent = -1;
        haffman[i].leftChild = -1;
        haffman[i].rightChild = -1;
    }

    for (int i = 0; i < n; i++)
    {
        cin >> haffman[i].weight;
    }

    //每次找出最小的权重的节点,生成新的节点,需要n - 1 次合并
    int x1, x2, w1, w2;
    for (int i = 0; i < n - 1; ++i)
    {
        x1 = x2 = -1;
        w1 = w2 = 10000;

        //注意这里每次是n + i次里面遍历
        for (int j = 0; j < n + i; ++j)
        {
            //得到最小权重的节点
            if (haffman[j].parent == -1 && haffman[j].weight <= w1)
            {
                //如果每次最小的更新了，那么需要把上次最小的给第二个最小的
                w2 = w1;
                x2 = x1;
                x1 = j;
                w1 = haffman[j].weight;
            }
            else if(haffman[j].parent == -1 && haffman[j].weight < w2)
            {//这里用else if而不是if,是因为它们每次只选1个就可以了。
                x2 = j;
                w2 = haffman[j].weight;
            }
        }
        //么次找到最小的两个节点后要记得合并成一个新的节点
        /*haffman[n + i].leftChild = x1;
        haffman[n + i].rightChild = x2;*/
        haffman[n + i].leftChild = x2;
        haffman[n + i].rightChild = x1;
        haffman[n + i].weight = w1 + w2;
        haffman[x1].parent = n + i;
        haffman[x2].parent = n + i;
    }
}
//打印每个字符的哈夫曼编码
void printCode(int n)
{
    //保存当前叶子节点的字符编码
    HaffmaCode hCode;
    //当前父节点
    int curParent;
    //下标和叶子节点的编号
    int c;
    //遍历的总次数
    for (int i = 0; i < n; ++i)
    {
        hCode.start = n - 1;
        c = i;
        curParent = haffman[i].parent;
        //遍历的条件是父节点不等于-1
        while (curParent != -1)
        {
            //我们先拿到父节点，然后判断左节点是否为当前值，如果是取节点0
            //否则取节点1,这里的c会变动，所以不要用i表示，我们用c保存当前变量i
            if (haffman[curParent].leftChild == c)
            {
                hCode.code[hCode.start] = 0;
            }
            else
            {
                hCode.code[hCode.start] = 1;
            }
            hCode.start--;
            c = curParent;
            curParent = haffman[c].parent;
        }
        //把当前的叶子节点信息保存到编码结构体里面
        for (int j = hCode.start + 1; j < n; ++j)
        {
            code[i].code[j] = hCode.code[j];
        }
        code[i].start = hCode.start;
    }
}
int main()
{
// 这样构建的树是小的在左边
// 然而题目要求小的在右边
    int cnt,k = 1;
    cin>>cnt;
    while(cnt--)
    {
        int n = 6;
        cin>>n;

        buildHaffman(n);

        printCode(n);

        cout<<"Case "<<k<<endl;
        for (int i = 0; i < n; ++i)
        {
            cout << haffman[i].weight << " ";
            for (int j = code[i].start + 1; j < n; ++j)
            {
                cout << code[i].code[j];
            }
            cout << endl;
        }
        k++;
    }
    return 0;


}


/**

2
6
9 8 3 4 1 2

8
60 20 5 5 3 3 3 1

 **/