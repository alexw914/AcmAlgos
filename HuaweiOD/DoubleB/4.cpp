//
// Created by Krisw on 2025/11/29.
//

/*
现需要在某城市进行 5G 网络建设，已经选取 N 个地点设置 5G 基站，编号固定为 1 到
N，接下来需要各个基站之间使用光纤进行连接以确保基
站能互联互通，不同基站之间架设光纤的成本各不相同，且有些节点之间已经存在光纤相连，请你设计算法，计算出能联通这些基站的最小成本是多少。
注意，基站的联通具有传递性，即基站 A 与基站 B 架设了光纤，基站 B 与基站 C 也架设了光纤，则基站 A 与基站 C
视为可以互相联通

输入描述
第一行输入表示基站的个数 N，其中 0 < N <= 20

第二行输入表示具备光纤直连条件的基站对的数目 M，其中 0 < M < N * (N - 1) / 2

第三行开始连续输入 M 行数据，格式为 X Y Z P，其中 X Y 表示基站的编号，0 < X <= N， 0 < Y <= N 且 X 不等于 Y， Z
表示在 X Y 之间架设光纤的成本，其中 0 < Z < 100，P 表示是否已存在光纤连接，0 表示未连接， 1 表示已连接。

输出描述
如果给定条件，可以建设成功互联互通的 5G 网络，则输出最小的建设成本，

如果给定条件，无法建设成功互联互通的 5G 网络，则输出-1

示例1：
输入
3
3
1 2 3 0
1 3 1 0
2 3 5 0
输出
4
说明
只需要在 1,2 以及 2,3 基站之间铺设光纤，其成本为 3+1=4

示例2
输入
3
1
1 2 5 0
输出
-1
说明
3 基站无法与其他基站连接，输出-1

示例3：
输入
3
3
1 2 3 0
1 3 1 0
2 3 5 1
输出
1
说明
2,3基站已有光纤相连，只有要再 1,3站点 2 向铺设，其成本为 1
 */

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
    int w;
};

int Find(vector<int>& p, int x) {
    if (p[x] != x) p[x] = Find(p, p[x]);
    return p[x];
}

void Union(vector<int>& p, int x, int y) {
    int fx = Find(p, x);
    int fy = Find(p, y);
    if (fx != fy) p[fx] = fy;
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<int> p(N + 1);
    for (int i = 1; i <= N; ++i) p[i] = i;

    vector<Edge> edges;  // 只存 P == 0 的边

    for (int i = 0; i < M; ++i) {
        int X, Y, Z, P;
        cin >> X >> Y >> Z >> P;
        if (P == 1) {  // 已有光纤，直接合并，无需成本
            Union(p, X, Y);
        } else {  // 需要花费 Z 才能铺设
            edges.push_back({X, Y, Z});
        }
    }

    // Kruskal：按成本排序
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) { return a.w < b.w; });

    int ans = 0;
    for (auto& e : edges) {
        int fx = Find(p, e.u);
        int fy = Find(p, e.v);
        if (fx != fy) {
            Union(p, fx, fy);
            ans += e.w;
        }
    }

    // 检查是否所有节点连通
    int root = Find(p, 1);
    for (int i = 2; i <= N; ++i) {
        if (Find(p, i) != root) {
            cout << -1 << endl;
            return 0;
        }
    }

    cout << ans << endl;
    return 0;
}
