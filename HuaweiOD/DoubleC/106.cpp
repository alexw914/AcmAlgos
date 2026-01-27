//
// Created by 巫妖王 on 2026/1/19.
//

/*
题目描述

现有一组砝码，重量互不相等，分别为m1,m2,m3…mn；
每种砝码对应的数量为x1,x2,x3...xn。现在要用这些砝码去称物体的重量，问能称出多少中不同的重量。

注：

称重重量包括0

输入描述:

输入包含多组测试数据。
对于每组测试数据：
第一行：n --- 砝码种数(范围[1,10])
第二行：m1 m2 m3 ... mn --- 每种砝码的重量(范围[1,2000])
第三行：x1 x2 x3 .... xn --- 每种砝码的数量(范围[1,6])

输出描述:

利用给定的砝码可以称出的不同的重量数

示例1

输入

2

1 2

2 1

输出

5
*/

#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> m(n), x(n);
    for (int i = 0; i < n; i++) cin >> m[i];
    for (int i = 0; i < n; i++) cin >> x[i];

    int maxSum = 0;
    for (int i = 0; i < n; i++) {
        maxSum += m[i] * x[i];
    }

    vector<char> dp(maxSum + 1, 0);
    dp[0] = 1; // 重量 0 一定可以

    for (int i = 0; i < n; i++) {
        int weight = m[i];
        int cnt = x[i];

        // 多重背包：逆序枚举
        for (int s = maxSum; s >= 0; s--) {
            if (!dp[s]) continue;
            for (int k = 1; k <= cnt; k++) {
                int ns = s + k * weight;
                if (ns > maxSum) break;
                dp[ns] = 1;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i <= maxSum; i++) {
        if (dp[i]) ans++;
    }

    cout << ans << "\n";

    return 0;
}
