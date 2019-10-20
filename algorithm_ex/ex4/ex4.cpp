//
// Created by 樊玲君 on 2019/10/19.
//
/**huffman code**/

//#include "stdafx.h"
#include "BinaryTree.h"
#include "MinHeap.h"
#include <iostream>
using namespace std;

const int N = 6;

template<class Type> class Huffman;

template<class Type>
BinaryTree<int> HuffmanTree(Type f[],int n);

template<class Type>
class Huffman
{
    friend BinaryTree<int> HuffmanTree(Type[],int);
public:
    operator Type() const
    {
        return weight;
    }
    //private:
    BinaryTree<int> tree;
    Type weight;
};

int main()
{
    char c[] = {'0','a','b','c','d','e','f'};
    int f[] = {0,45,13,12,16,9,5};//下标从1开始
    BinaryTree<int> t = HuffmanTree(f,N);

    cout<<"the frequency of every character:"<<endl;
    for(int i=1; i<=N; i++)
    {
        cout<<c[i]<<":"<<f[i]<<" ";
    }
    cout<<endl;

    cout<<"Pre Order:"<<endl;
    t.Pre_Order();
    cout<<endl;

    cout<<"In Order:"<<endl;
    t.In_Order();
    cout<<endl;

    t.DestroyTree();
    return 0;
}

template<class Type>
BinaryTree<int> HuffmanTree(Type f[],int n)
{
    //生成单节点树
    Huffman<Type> *w = new Huffman<Type>[n+1];
    BinaryTree<int> z,zero;

    for(int i=1; i<=n; i++)
    {
        z.MakeTree(i,zero,zero);
        w[i].weight = f[i];
        w[i].tree = z;
    }

    //建优先队列
    MinHeap<Huffman<Type>> Q(n);
    for(int i=1; i<=n; i++) Q.Insert(w[i]);

    //反复合并最小频率树
    Huffman<Type> x,y;
    for(int i=1; i<n; i++)
    {
        x = Q.RemoveMin();
        y = Q.RemoveMin();
        z.MakeTree(0,x.tree,y.tree);
        x.weight += y.weight;
        x.tree = z;
        Q.Insert(x);
    }

    x = Q.RemoveMin();

    delete[] w;

    return x.tree;
}