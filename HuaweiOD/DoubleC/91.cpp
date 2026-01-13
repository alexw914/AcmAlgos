//
// Created by 巫妖王 on 2026/1/13.
//

/*
题目描述
在某商场的地下停车场，部署了一套智能导航系统。停车场可以看作是一个 r*c
的网格矩阵，其中：

0 表示该位置是空的行车道，车辆可以通行。
1 表示该位置存有障碍物、立柱或其他已停放的车辆，车辆无法通行。
停车场的入口统一设在坐标 [0, 0]
处。现在有一辆车进入停车场，需要前往指定的目标车位 [m, n]。

车辆在停车场内只能沿着上、下、左、右四个方向移动，每移动一个格子计为步数
1。请你帮车主规划一条从入口到目标车位的最短路径。

输入描述
第一行输入两个整数 m 和 n，表示目标车位的行下标和列下标。
第二行输入两个整数 row 和 col，表示停车场的总行数和总列数。
接下来的 row 行，每行包含 col 个以空格分隔的整数（0 或
1），表示停车场的状态信息。 约束条件：

1 < row, col < 200
0 < m < row, 0 < n < col
入口 [0, 0] 保证为空位。
输出描述
输出一个整数，表示从入口 [0, 0] 到目标车位 [m, n] 的最短路径步数。
如果由于障碍物阻挡无法到达目标位置，则输出 -1。
示例 1
输入：

1 1

3 3

0 0 0

0 0 0

0 0 0

输出：

2

说明：

停车场大小为 3x3，目标位置在 [1, 1]。

最短路径序列可为：[0, 0] -> [0, 1] -> [1, 1]，共移动 2 步。

或者：[0, 0] -> [1, 0] -> [1, 1]，共移动 2 步。

示例 2
输入：

2 2

3 3

0 1 0

1 1 0

0 0 0

输出：

-1

说明：

由于入口 [0, 0] 的右边 [0, 1] 和下边 [1, 0]
均为障碍物（1），车辆被困在入口处，无法到达目标位置 [2, 2]，因此输出 -1。

示例 3
输入：

0 2

3 3

0 0 0

1 1 0

0 0 0

输出：

2

说明：

目标位置在 [0, 2]。虽然中间有障碍物，但可以沿着第一行直接向右行驶：[0, 0] -> [0,
1] -> [0, 2]，步数为 2。
*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n, row, col;
    cin >> m >> n >> row >> col;

    vector<vector<int> > g(row, vector<int>(col, 0));
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) { cin >> g[i][j]; }
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    vector<vector<int> > vis(row, vector<int>(col, 0));

    queue<pair<int, int> > q;
    q.push(make_pair(0, 0));
    vis[0][0] = 1;

    int step = 0;
    bool found = false;
    while (!q.empty() && !found) {
        auto sz = q.size();
        for (int i = 0; i < sz; i++) {
            auto [x, y] = q.front();
            q.pop();
            if (x == m && y == n) {
                found = true;
                break;
            }
            for (int k = 0; k < 4; k++) {
                auto nx = x + dx[k];
                auto ny = y + dy[k];
                if (nx >= 0 && nx < row && ny >= 0 && ny < col && !g[nx][ny] && !vis[nx][ny]) {
                    vis[nx][ny] = 1;
                    q.push({nx, ny});
                }
            }
        }
        if (!found) { step++; }
    }

    cout << (found ? step : -1) << endl;

    return 0;
}
