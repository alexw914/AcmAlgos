//
// Created by Krisw on 2026/3/22.
//

/*
宝宝和妈妈参加亲子游戏，在一个二维矩阵（N*N）的格子地图上，宝宝和妈妈抽签决定各自的位置，地图上每个格子有不同的糖果数量，部分格子有障碍物。

游戏规则是妈妈必须在最短的时间（每个单位时间只能走一步）到达宝宝的位置，路上的所有糖果都可以拿走，不能走障碍物的格子，只能上下左右走。

请问妈妈在最短到达宝宝位置的时间内最多拿到多少糖果（优先考虑最短时间到达的情况下尽可能多拿糖果）。

输入描述
第一行输入为N，N标识二维矩阵的大小

之后N行，每行有N个值，表格矩阵每个位置的值

其中：

-3：妈妈
-2：宝宝
-1：障碍
>=0：糖果数(0表示没有糖果，但是可以走)


输出描述
输出妈妈在最短到达宝宝位置的时间内最多拿到多少糖果，行末无多余空格

备注
地图最大50*50

示例1：
输入
4
3 2 1 -3
1 -1 1 1
1 1 -1 2
-2 1 2 3
输出
9
说明
此地图有两条最短路径可到宝宝位置，都是最短路径6步，但先向下再向左可以拿到9个糖果

示例2：
输入
4
3 2 1 -3
-1 -1 1 1
1 1 -1 2
-2 1 -1 3
输出
-1
说明
此地图妈妈无法到达宝宝位置
 */

#include <iostream>
#include <queue>
#include <vector>
#include <sstream>
#include <climits>
using namespace std;

struct Node {
    int x, y;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<vector<int>> maze(N, vector<int>(N));
    pair<int, int> mum_pos, baby_pos;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> maze[i][j];
            if (maze[i][j] == -3) mum_pos = {i, j};
            if (maze[i][j] == -2) baby_pos = {i, j};
        }
    }

    const int INF = INT_MAX;
    vector<vector<int>> dist(N, vector<int>(N, INF));
    vector<vector<int>> best(N, vector<int>(N, -1));

    queue<Node> q;

    int sx = mum_pos.first, sy = mum_pos.second;
    int tx = baby_pos.first, ty = baby_pos.second;

    dist[sx][sy] = 0;
    best[sx][sy] = 0;
    q.push({sx, sy});

    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, -1, 0, 1};

    while (!q.empty()) {
        auto cur = q.front();
        q.pop();

        int x = cur.x, y = cur.y;

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            if (maze[nx][ny] == -1) continue;  // 障碍物不能走

            int nd = dist[x][y] + 1;
            int gain = (maze[nx][ny] >= 0) ? maze[nx][ny] : 0;
            int nc = best[x][y] + gain;

            // 第一次到达，或者发现更短路
            if (nd < dist[nx][ny]) {
                dist[nx][ny] = nd;
                best[nx][ny] = nc;
                q.push({nx, ny});
            }
            // 同样是最短路，但糖果更多
            else if (nd == dist[nx][ny] && nc > best[nx][ny]) {
                best[nx][ny] = nc;
                q.push({nx, ny});
            }
        }
    }

    if (dist[tx][ty] == INF) {
        cout << -1 << '\n';
    } else {
        cout << best[tx][ty] << '\n';
    }

    return 0;
}