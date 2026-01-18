//
// Created by Krisw on 2026/1/16.
//

/*
快递公司每日早晨，给每位快递员推送需要送到客户手中的快递以及路线信息，快递员自己又查找了一些客户与客户之间的路线距离信息，
请你依据这些信息，给快递员设计一条最例短路径，告诉他最短路径的距离。注意:
1.不限制快递包裹送到客户手中的顺序，但必须保证都送到客户手中
2.用例保证一定存在投递站到每位客户之间的路线，但不保证客户与客户之间有路线，客户位置及投递站均允许多次经过。
3.所有快递送完后，快递员还需要回到投递站


输入描述
首行输入两个正整数n, m。
接下面n行，输入快递公司发布的客户快递信息，
格式为: 客户id 投递站到客户之间的距离distance
再接下来的m行，是快递员自行查找的客户与客户之间的距离信息格式为: 客户1id 客户2id distance
在每行数据中，数据与数据之间均以单个空格分割。

规格;
0<n <=10
0 <= m <= 10
0<客户id <= 1000
0< distance <= 10000
输出描述
最短路径距离，如无法找到，请输出 -1

示例1：

输入：

2 1
1 1000
2 1200
1 2 300

输出：

2500

说明：
路径1:快递员先把快递送到客户1手中，接下来直接走客户1到客户2之间的直通路线，最后走投递站与客户2之间的路，回到投递站，距离为1000 + 300 + 1200 = 2500

路径2: 快递员先把快递送到客户1手中，接下来回快递站，再出发把客户2的快递送到，在返回到快递站，距离为: 1000 + 10001200 + 1200 = 4400
路径3:快递员先把快递送到客户2手中，接下来直接走客户2到客户1之间的直通线路，最后走投递站和客户1之间的路，回到投递站，距离为1200 + 300 + 1000 =2500
所有路径中，最短路径距离为2500

示例2：

输入：

5  1
5 1000
9 1200
17 300
132 700
500 2300
5 9 400

输出：

9200

说明: 在所有可行的路径中，最短路径长度为1000 + 400 + 1200 + 300 + 300 + 700 + 700 + 2300 + 2300 = 9200
*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <climits>
using namespace std;

static const long long INF = LLONG_MAX / 4;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // 映射客户id -> 1..n
    unordered_map<int,int> id2idx;
    vector<int> idx2id(n + 1);

    vector<long long> depotDist(n + 1);

    for (int i = 1; i <= n; i++) {
        int id;
        long long d;
        cin >> id >> d;
        id2idx[id] = i;
        idx2id[i] = id;
        depotDist[i] = d;
    }

    int total = n + 1; // 0 = depot

    vector<vector<long long>> dist(total, vector<long long>(total, INF));

    for (int i = 0; i < total; i++) dist[i][i] = 0;

    // depot <-> customers
    for (int i = 1; i <= n; i++) {
        dist[0][i] = dist[i][0] = depotDist[i];
    }

    // customer-customer edges
    for (int i = 0; i < m; i++) {
        int a, b;
        long long d;
        cin >> a >> b >> d;
        if (id2idx.count(a) && id2idx.count(b)) {
            int u = id2idx[a];
            int v = id2idx[b];
            dist[u][v] = min(dist[u][v], d);
            dist[v][u] = min(dist[v][u], d);
        }
    }

    // Floyd-Warshall
    for (int k = 0; k < total; k++)
        for (int i = 0; i < total; i++)
            for (int j = 0; j < total; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    // 可达性检查
    for (int i = 1; i <= n; i++) {
        if (dist[0][i] >= INF) {
            cout << -1 << "\n";
            return 0;
        }
    }

    int FULL = 1 << n;
    vector<vector<long long>> dp(FULL, vector<long long>(n, INF));

    // 初始化
    for (int i = 0; i < n; i++) {
        dp[1 << i][i] = dist[0][i + 1];
    }

    // 状态转移
    for (int mask = 1; mask < FULL; mask++) {
        for (int i = 0; i < n; i++) {
            if (!(mask & (1 << i))) continue;
            long long cur = dp[mask][i];
            if (cur >= INF) continue;

            for (int j = 0; j < n; j++) {
                if (mask & (1 << j)) continue;
                int nextMask = mask | (1 << j);
                dp[nextMask][j] = min(dp[nextMask][j],
                    cur + dist[i + 1][j + 1]);
            }
        }
    }

    long long ans = INF;
    int fullMask = FULL - 1;
    for (int i = 0; i < n; i++) {
        ans = min(ans, dp[fullMask][i] + dist[i + 1][0]);
    }

    if (ans >= INF) cout << -1 << "\n";
    else cout << ans << "\n";

    return 0;
}


