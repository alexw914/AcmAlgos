//
// Created by Krisw on 2025/12/22.
//

/*
题目描述
祖国西北部有一片大片荒地，其中零星的分布着一些湖泊，保护区，矿区.整体上常年光照良好，但是也有一些地区光照不太好。
某电力公司希望在这里建设多个光伏电站，生产清洁能源对每平方公里的土地进行了发电评估，其中不能建设的区域发电量为0kw，
可以发电的区域根据光照，地形等给出了每平方公里年发电量x千瓦。我们希望能够找到其中集中的矩形区域建设电站，能够获得良好的收益.
输入描述
第一行输入为调研的地区长，宽，以及准备建设的电站【长宽相等，为正方形】的边长最低要求的发电量

之后每行为调研区域每平方公里的发电量
输出描述
输出为这样的区域有多少个

示例1：

输入
2 5 2 6
1 3 4 5 8
2 3 6 7 1

输出

4
输入说明
调研的区域大小为长2宽5的矩形，我们要建设的电站的边长为2，建设电站最低发电量为6.
输出说明

长宽为2的正方形满足发电量大于等于6的区域有4个

示例2：

输入

2 5 1 6
1 3 4 5 8
2 3 6 7 1
输出
3
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N, S;
    long long V;
    cin >> M >> N >> S >> V;

    vector<vector<long long>> a(M + 1, vector<long long>(N + 1, 0));
    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) cin >> a[i][j];
    }

    // 二维前缀和：pre[i][j] = sum of a[1..i][1..j]
    vector<vector<long long>> prefix(M + 1, vector<long long>(N + 1, 0));
    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1] + a[i][j];
        }
    }

    auto GetRectSum = [&](int x1, int y1, int x2, int y2) -> long long {
        // 闭区间 (x1,y1) 到 (x2,y2)
        return prefix[x2][y2] - prefix[x1 - 1][y2] - prefix[x2][y1 - 1] + prefix[x1 - 1][y1 - 1];
    };

    long long ans = 0;
    if (S <= M && S <= N) {
        for (int i = 1; i + S - 1 <= M; i++) {
            for (int j = 1; j + S - 1 <= N; j++) {
                int x2 = i + S - 1, y2 = j + S - 1;
                long long sum = GetRectSum(i, j, x2, y2);
                if (sum >= V) ans++;
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
