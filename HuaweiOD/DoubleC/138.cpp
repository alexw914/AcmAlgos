//
// Created by Krisw on 2026/2/21.
//

/*
有一个大小是N*M的战场地图，被墙壁 '#' 分隔成大小不同的区域，上下左右四个方向相邻的空地 '.'，属于同一个区域，只有空地上可能存在敌人'E'，请求出地图上总共有多少区域里的敌人数小于K。
输入描述
第一行输入为N.M.K;
N表示地图的行数，M表示地图的列数，K表示目标敌人数量
N，M<=100
之后为一个NxM大小的字符数组
输出描述
敌人数小于K的区域数量

示例1：

输入
3 5 2
..#EE
E.#E.
###..

输出
1
说明
地图被墙壁分为两个区域，左边区域有1个敌人，右边区域有3个敌人，符合条件的区域数量是1
*/

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

char g[110][110];
int N, M, K;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int bfs(int si, int sj, vector<vector<char>>& vis) {
    int enemy = 0;
    queue<pair<int,int>> q;
    q.push({si, sj});
    vis[si][sj] = 1;

    while (!q.empty()) {
        auto cur = q.front(); q.pop();
        int x = cur.first, y = cur.second;

        if (g[x][y] == 'E') enemy++;

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx >= 0 && nx < N && ny >= 0 && ny < M &&
                g[nx][ny] != '#' && !vis[nx][ny]) {
                vis[nx][ny] = 1;
                q.push({nx, ny});
                }
        }
    }
    return enemy;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> K;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) cin >> g[i][j];
    }

    int ans = 0;
    vector<vector<char>> vis(N, vector<char>(M, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (g[i][j] != '#' && !vis[i][j]) {
                int num = bfs(i, j, vis);
                if (num < K) ans++;
            }
        }
    }
    cout << ans << "\n";
    return 0;
}