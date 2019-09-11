//
// Created by 樊玲君 on 2019/9/3.
//

#include <iostream>
#include<algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

int board[9999][9999] = {0};
int tile = 0;

void ChessBoard(int n,int x,int y,int s_x,int s_y)
{
    // 参数说明：
    // n : 棋盘规格
    // x,y : 在当前棋盘内特殊点所在的坐标位置
    // s_x,s_y : 当前棋盘定位（左上角位置）

    if (n == 1)
        return;

    int half_n = n/2;

    int l_count = ++tile;// 骨牌编号

    //左上角
    if (x < s_x + half_n&&y < s_y + half_n)
    {// 若特殊点在此棋盘内，则缩小棋盘范围
        ChessBoard(half_n,x,y,s_x,s_y);
    }
    else
    {// 将右下角放个放骨牌，并且以该位置为特殊点进入递归
        board[s_x + half_n - 1][s_y+ half_n - 1] = l_count;
        ChessBoard(half_n,s_x + half_n - 1,s_y + half_n - 1,s_x,s_y);
    }

    //右上角
    if (x >= s_x + half_n&&y < s_y + half_n)
    {
        ChessBoard(half_n,x,y,s_x + half_n,s_y);
    }
    else
    {
        board[s_x + half_n][s_y + half_n - 1] = l_count;
        ChessBoard(half_n,s_x + half_n,s_y + half_n - 1,s_x + half_n,s_y);
    }

    //左下角
    if (x < s_x + half_n&&y >= s_y + half_n)
    {
        ChessBoard(half_n,x,y,s_x,s_y + half_n);
    }
    else
    {
        board[s_x + half_n - 1][s_y + half_n] = l_count;
        ChessBoard(half_n,s_x + half_n - 1,s_y + half_n,s_x,s_y + half_n);
    }

    //右下角
    if (x >= s_x + half_n&&y >= s_y + half_n)
    {
        ChessBoard(half_n,x,y,s_x + half_n,s_y + half_n);
    }
    else
    {
        board[s_x + half_n][s_y + half_n] = l_count;
        ChessBoard(half_n,s_x + half_n,s_y + half_n,s_x + half_n,s_y + half_n);
    }



}


int main() {

    int size,x,y,length;
    int n = 0;
    char c = '#';
    int input[100][3];
    cout<<"please input the size,x,y:"<<endl;

    while (cin>>size>>x>>y)
    {
        if (size == '#')
            break;
        input[n][0] = size;
        input[n][1] = x;
        input[n][2] = y;
        n++;
    }


    for (int i = 0;i < n;i++)
    {

        size = input[i][0];
        x = input[i][1];
        y = input[i][2];
        length = pow(2,size);
        if (size < 0 || x < 0 || y < 0)
            cout<<"Case "<< i + 1 <<": Error!"<<endl;
        else if (x >= length || y >= length)
            cout<<"Case "<< i + 1 <<": Error!"<<endl;
        else
        {

            board[x][y] = -1;
            tile = 0;
            ChessBoard(length,x,y,0,0);
            cout<<"Case "<< i + 1 <<": n = "<<length<<endl;
            for (int i = 0;i < length;i++)
            {
                for (int j = 0;j < length;j++)
                {
                    if (i == x&&j == y)
                        cout<<setw(5)<<c<<" ";
                    else
                        cout<<setw(5)<<board[i][j]<<" ";
                }
                cout<<endl;
            }
        }



    }
    return 0;
}