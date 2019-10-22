//
// Created by 樊玲君 on 2019/10/20.
//
/**马的哈密顿周游问题**/

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <iostream>


using namespace std;

int n, m;
int a[100][100]; // 表示棋盘
struct Point {
    int x,y;
};
Point every_point[10005];
// if n == 3
// {
// (1,2),(1,2),(1,2),(1,2),(1,2),(1,2),(1,2),(1,2),(1,2),(1,2)
// (1,2),(1,2),(1,2),
// (1,2),(1,2),(1,2),
// (1,2),(1,2),(1,2),
// (1,2),
// }
// 2 2

//定义马走的8个方向
int direction[8][2]={
        {-2,-1},{2,-1},{-2,1},{2,1},{-1,-2},{-1,2},{1,-2},{1,2}
};

void Show()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cout<<"("<<every_point[i * n + j + 1].x<<","<<every_point[i * n + j + 1].y<<") ";
        cout<<endl;
    }
    cout << endl << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }
}

bool judge(int x, int y)
{
    for (int i = 0; i < 8; i++) {
        if (x + direction[i][0] == 0 && y + direction[i][1] == 0)
            return true;
    }
    return false;
}

void DFS(int cur_x, int cur_y, int step)
{

    if (step == n * m + 1 && judge(cur_x, cur_y)) {
        Show();
        exit(0);
    }

    int tmp_x, tmp_y;
    for (int i = 0; i < 8; i++) {
        // 存储点坐标
        tmp_x = cur_x + direction[i][0];
        tmp_y = cur_y + direction[i][1];
        if (tmp_x < 0 || tmp_x >= n || tmp_y < 0 || tmp_y >= m || a[tmp_x][tmp_y] != 0)
            continue;
        every_point[step].x = tmp_x;
        every_point[step].y = tmp_y;

        a[tmp_x][tmp_y] = step;
        DFS(tmp_x, tmp_y, step + 1);
        a[tmp_x][tmp_y] = 0;
    }
}


int main()
{
    cin>>n>>m;
    // 每个棋盘是m行n列
    a[0][0] = 1;
    every_point[1].x = 0;
    every_point[1].y = 0;
    DFS(0, 0, 2);
    Show();
    return 0;
}
