//
// Created by Krisw on 2025/12/3.
//
/*
给定一个 n
个点 m
条边的有向图，图中可能存在重边和自环，边权可能为负数。

再给定 k
个询问，每个询问包含两个整数 x
和 y
，表示查询从点 x
到点 y
的最短距离，如果路径不存在，则输出 impossible。

数据保证图中不存在负权回路。

输入格式
第一行包含三个整数 n,m,k
。

接下来 m
行，每行包含三个整数 x,y,z
，表示存在一条从点 x
到点 y
的有向边，边长为 z
。

接下来 k
行，每行包含两个整数 x,y
，表示询问点 x
到点 y
的最短距离。

输出格式
共 k
行，每行输出一个整数，表示询问的结果，若询问两点间不存在路径，则输出 impossible。

数据范围
1≤n≤200
,
1≤k≤n2

1≤m≤20000
,
图中涉及边长绝对值均不超过 10000
。

输入样例：
3 3 2
1 2 1
2 3 2
1 3 1
2 1
1 3
输出样例：
impossible
1
*/

#include <bits/stdc++.h>
using namespace std;

void floyd(vector<vector<int> > &graph) {
    const int N = graph.size() - 1;
    for (int k = 1; k <= N; ++k) {
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
            }
        }
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> graph(n + 1, vector<int>(m + 1, 0x3f3f3f));

    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u][v] = min(w, graph[u][v]);
    }

    floyd(graph);

    while (k--) {
        int u, v;
        cin >> u >> v;
        int dist = graph[u][v];
        if (dist > 0x3f3f3f / 2) cout << "impossible" << endl;
        else cout << dist << endl;
    }
    return 0;
}
