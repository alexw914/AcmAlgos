//
// Created by Krisw on 2025/12/9.
//
/*
给定一个二维的m*n网格地图(grids二维数组)，每个单元格0为空，1是障碍物，2是红绿灯;每一步可以在0或者2的单元格移动，每一秒可以走一个单元格;
遇到红绿灯想要通过需要等待不同的时间才能通过，大小为x的light数组标注灯的坐标和等待时间，
例如(2,2.3),坐标(2,2)红绿灯等待时间3秒，问从左上角(0,0)到右下角(m-1,n-1)所需的最短时间。

输入描述
第一行输入 grids 二维数组，内部数据只有0，1，2，1<m,n<=100
第二行输入 lights 红绿灯二维数组，1<x<=m*n
输出描述
从坐标(0,0)到(m-1,n-1)坐标所需的最短时间，如果没有路径，则返回最短时间为-1.

示例1
输入
[[0,1,0],[0,2,1],[0,0,0]]
[[1,1,3]]
输出
4
 */

#include <bits/stdc++.h>
using namespace std;

vector<vector<int> > ParseInput(const string &line) {
    vector<vector<int> > result;
    if (line.empty() || line.length() < 4) return result;

    string temp_line = line.substr(1, line.length() - 2);

    vector<int> current_row;
    string current_num_str;
    bool in_row = false;

    for (char c: temp_line) {
        if (c == '[') {
            current_row.clear();
            in_row = true;
        } else if (c == ']') {
            if (!current_num_str.empty()) {
                current_row.push_back(stoi(current_num_str));
                current_num_str = "";
            }
            if (in_row) result.push_back(current_row);
            in_row = false;
        } else if (isdigit(c) || c == '-') {
            current_num_str += c;
        } else if (c == ',') {
            if (!current_num_str.empty()) {
                current_row.push_back(stoi(current_num_str));
                current_num_str = "";
            }
        }
    }
    return result;
}

int Dijkstra(vector<vector<int>>& graph) {
    const int N = graph.size() - 1;
    vector<int> dist(N, 0x3f3f3f);
    vector<bool> st(N, false);

    dist[1] = 0;
    for (int i = 1; i < N; i++) {
        int t = -1;
        for (int j = 1; j < N; j++) {
            if (!st[j] && (t == -1 || dist[t] > dist[j])) {
                t = j;
            }
        }
        if (t == -1 || dist[t] == 0x3f3f3f) break;
        st[t] = true;
        for (int k = 1; k <= N; k++) {
            if (graph[t][k] == 0x3f3f3f) continue;         // 没边就跳过
            dist[k] = min(dist[k], dist[t] + graph[t][k]);
        }
    }
    if (dist[N] == 0x3f3f3f) return -1;
    return dist[N];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    getline(cin, s);
    auto grids = ParseInput(s);

    getline(cin, s);
    auto lights = ParseInput(s);

    const int m = grids.size();
    const int n = grids[0].size();
    // 起点或终点是障碍物，直接无解
    if (grids[0][0] == 1 || grids[m - 1][n - 1] == 1) {
        cout << -1 << "\n";
        return 0;
    }

    int N = m * n;
    vector<vector<int> > wait(m, vector<int>(n, 0));
    for (auto &L: lights) {
        auto x = L[0], y = L[1], t = L[2];
        if (x >= 0 && x < m && y >= 0 && y < n) { wait[x][y] = t; }
    }

    // 编号函数：把 (x,y) 映射到 1..N
    auto GetID = [n](int x, int y) {
        return x * n + y + 1;
    };

    // 建邻接矩阵，初始为 INF，自身到自身为 0
    vector<vector<int> > g(N + 1, vector<int>(N + 1, 0x3f3f3f));
    for (int i = 1; i <= N; i++) g[i][i] = 0;

    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    for (int x = 0; x < m; x++) {
        for (int y = 0; y < n; y++) {
            if (grids[x][y] == 1) continue; // 障碍物不出边

            int u = GetID(x, y);
            for (int dir = 0; dir < 4; dir++) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                // 越界
                if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
                // 目标是障碍物，也不能走
                if (grids[nx][ny] == 1) continue;

                int v = GetID(nx, ny);
                int cost = 1 + wait[nx][ny];  // 走一步 + 若为红绿灯则等待

                // 无向图，允许来回走
                g[u][v] = min(g[u][v], cost);
                g[v][u] = min(g[v][u], cost);
            }
        }
    }

    cout <<  Dijkstra(g) << "\n";
    return 0;
}