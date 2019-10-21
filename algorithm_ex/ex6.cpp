//
// Created by 樊玲君 on 2019/10/21.
//

/**跳马问题**/
/**
 * 根据分析，每个马最多有八个方位可走
 *
设马原来在（x,y），则：
Step1:(x – 1,y + 2)
Step2:(x + 1,y + 2)
Step3:(x – 2,y + 1)
Step4:(x – 2,y - 1)
Step5:(x – 1,y - 2)
Step6:(x + 1,y - 2)
Step7:(x + 2,y + 1)
Step8:(x + 2,y - 1)
 *
 *
 *
 * **/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

// 定义棋盘&已经看过的位置
int ChessBoard[8][8];
// 定义马可能走的8个方向
/*int direction[8][2] = {
    {-1,2},{1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,1},{2,-1}
};*/


int direction[8][2]={
        {-2,-1},{2,-1},{-2,1},{2,1},{-1,-2},{-1,2},{1,-2},{1,2}
};


// 定义始末位置坐标
char x1,x2;
int s_x,s_y,t_x,t_y;

// 定义结构体存储每个点
struct Point{
    int x,y;
    int steps;
}buffer;

queue<Point> q;

bool IsCorrect(int x,int y)
// 判断当前坐标是否合法
{
    if (x < 0||x >= 8||y < 0||y >= 8)
        return false;
    return true;
}

int BFS()
{
    ChessBoard[s_x][s_y] = 1;

    while(!q.empty()) // 当队列不为空的时候
    {
        // 获取队头的元素的坐标，注意，这时候我们不急着取出元素
        int cur_x = q.front().x;
        int cur_y = q.front().y;

        for (int i = 0;i < 8;i++)
        {
            buffer.x = cur_x + direction[i][0];
            buffer.y = cur_y + direction[i][1];

            if (IsCorrect(buffer.x,buffer.y)&&ChessBoard[buffer.x][buffer.y] == 0)
            // 两个条件：坐标在棋盘内、这个点没被看过
            {
                buffer.steps = q.front().steps + 1;
                ChessBoard[buffer.x][buffer.y] = 1;
                q.push(buffer);
                if ((buffer.x == t_x)&&(buffer.y == t_y))
                    break;
            }
        }
        q.pop();
        //  a1==>a2: 3 moves
        if ((buffer.x == t_x)&&(buffer.y == t_y))
        {

            cout<<x1<<s_y<<"==>"<<x2<<t_y<<": "<<buffer.steps<<" moves"<<endl;
            break;
        }

    }

}


int main()
{
    while (cin>>x1>>s_y>>x2>>t_y)
    {
        // 为了方便，更加符合计算内内部的要求我们都让它从0开始
        s_x = x1 - 'a';
        s_y = s_y - 1;
        t_x = x2 - 'a';
        t_y = t_y - 1;

        if ((s_x == t_x)&&(s_y == t_y))
            cout<<" 0 moves"<<endl;
        else
        {
            // 利用结构体类型初始化一个队列
            while (!q.empty())
                q.pop();

            memset(ChessBoard,0,sizeof(ChessBoard));// 初始化棋盘全部为0

            buffer.x = s_x;
            buffer.y = s_y;
            buffer.steps = 0;
            q.push(buffer); // 把起点入队列

            BFS();
        }
    }

    return 0;
}
