//
// Created by Krisw on 2025/12/2.
//

/*
给定一个 n
个点 m
条边的有向图，图中可能存在重边和自环，所有边权均为正值。

请你求出 1
号点到 n
号点的最短距离，如果无法从 1
号点走到 n
号点，则输出 −1
。

输入格式
第一行包含整数 n
和 m
。

接下来 m
行每行包含三个整数 x,y,z
，表示存在一条从点 x
到点 y
的有向边，边长为 z
。

输出格式
输出一个整数，表示 1
号点到 n
号点的最短距离。

如果路径不存在，则输出 −1
。

数据范围
1≤n≤500
,
1≤m≤105
,
图中涉及边长均不超过10000。

输入样例：
3 3
1 2 2
2 3 1
1 3 4
输出样例：
3
*/

#include <bits/stdc++.h>
using namespace std;

int Dijkstra(vector<vector<int> > &g) {
    const auto N = g.size() - 1;
     // 起始点到其他点的距离
    vector<int> dist(N + 1, 0x3f3f3f);
    // 已经确定最短距离的点
    vector<bool> st(N + 1, false);

    dist[1] = 0;
    for (int i = 1; i <= N; i++) {
        int t = -1;
        for (int j = 1; j <= N; j++) {         // 不在st中，距离最短的点
            if (!st[j] && (t == -1 || dist[t] > dist[j])) {
                t = j;
            }
        }
        st[t] = true;
        for (int k = 1; k <= N; k++) {         // 更新其它点距离
            dist[k] = min(dist[k], dist[t] + g[t][k]);
        }
    }
    if (dist[N] == 0x3f3f3f) return -1;
    return dist[N];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<vector<int> > g(N + 1, vector<int>(N + 1, 0x3f3f3f));
    while (M--) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u][v] = min(g[u][v], w);
    }

    cout << Dijkstra(g) << endl;
    return 0;
}
