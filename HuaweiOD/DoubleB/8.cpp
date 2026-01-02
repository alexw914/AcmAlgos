//
// Created by Krisw on 2025/11/30.
//
/*
机器人走一个迷宫，给出迷宫的x和y(x*y的迷宫)并且迷宫中有障碍物,输入k表示障碍物有k个，并且会将障碍物的坐标挨个输入。

机器人从0,0的位置走到x,y的位置并且只能向x,y增加的方向走，不能回退，

如代码类注释展示的样子，#表示可以走的方格，0代表障碍，机器人从0,0的位置只能向下或者向前走到出口，

其中会有不可达方格和陷阱方格。

不可达方格为第四行前三个，该机器人在行走路径上不可能走到的方格，陷阱方格如第一行最后两个，走进之后则不能抵达终点。

要求: 输出陷阱和不可达方格方格数量。

输入描述：

1）第一行为房间的X 和Y （0<=X/Y <=1000）

2)  第一行为房间中的墙壁障碍物个数 N，0<= N <=X*Y ）

3)  接下来会有N行墙壁的坐标，同一行中若有多个障碍物，以空格隔开，所有数据输入均合法。

输出描述：

陷阱方格与不可达方格数量，以空格隔开。

示例1：

输入：

6 4

5

0 2

1 2

2 2

4 1

5 1

输出：

2 3
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int M, N;
    cin >> M >> N;

    int K;
    cin >> K;
    vector<vector<char>> matrix(M, vector<char>(N, '#'));
    while (K--) {
        int x, y;
        cin >> x >> y;
        matrix[x][y] = 'O';
    }

    vector<vector<bool>> vis(M, vector<bool>(N, false));
    // 能到的格子
    vector<vector<bool>> canArrive(M, vector<bool>(N, false));
    // 能到终点的格子
    vector<vector<bool>> canToEnd(M, vector<bool>(N, false));


    queue<pair<int, int>> q;
    if (matrix[0][0] == '#') {              // 起点不是障碍才开始搜索
        q.push({0, 0});
        vis[0][0] = true;
        canArrive[0][0] = true;
    }
    int ddx[2] = {1, 0};
    int ddy[2] = {0, 1};
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int i = 0; i < 2; i++) {
            auto nx = x + ddx[i];
            auto ny = y + ddy[i];
            if (nx >= 0 && nx < M && ny >= 0 && ny < N && matrix[nx][ny] == '#' && !vis[nx][ny]) {
                vis[nx][ny] = true;
                q.push({nx, ny});
                canArrive[nx][ny] = true;
            }
        }
    }

    vis.assign(M, vector<bool>(N, false));

    if (matrix[M - 1][N - 1] == '#') {      // 终点不是障碍才开始搜索
        q.push({M - 1, N - 1});
        vis[M - 1][N - 1] = true;
        canToEnd[M - 1][N - 1] = true;
    }

    int udx[2] = {-1, 0};
    int udy[2] = {0, -1};
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int i = 0; i < 2; i++) {
            auto nx = x + udx[i];
            auto ny = y + udy[i];
            if (nx >= 0 && nx < M && ny >= 0 && ny < N && matrix[nx][ny] == '#' && !vis[nx][ny]) {
                vis[nx][ny] = true;
                q.push({nx, ny});
                canToEnd[nx][ny] = true;
            }
        }
    }

    int unreachNum = 0, trapNum = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] == 'O') continue;
            if (!canArrive[i][j]) { unreachNum++; }
            if (canArrive[i][j] && !canToEnd[i][j]) { trapNum++; }
        }
    }
    cout << trapNum << " " << unreachNum << '\n';
    return 0;
}
