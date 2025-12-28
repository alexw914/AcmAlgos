//
// Created by Krisw on 2025/12/27.
//

/*
一、题目描述
小朋友考试得第一名就可以得到零食奖励。

现在价格A、B、C、D、E、…，元商品名A1、B1、C1、D1、E1、…，小朋友的喜爱度依次为A2、B2、C2、D2、E2、…。

请返回选取x元零食可以达到的最大喜爱度。

二、输入描述
第一行输入为x和N，x为可使用的钱的总额，N为零食种类数。

0 ≤ x ≤ 1000
0 ≤ N ≤ 100

第二行开始为零食属性，每行有三个整型数值，分别代表零食的价格、数量和喜爱度。

零食价格(0,100)
零食个数[0,10000]
零食喜爱度[0,10000]


三、输出描述
最大喜爱度

四、测试用例
示例1：
输入:
10 2
2 4 3
3 3 4

输出:
14

说明:
可选第1种零食最多 4 个，第2种最多 3 个。最佳选择为：选 2 个第2种（花费 6 元，喜爱度 8）和 2 个第1种（花费 4 元，喜爱度 6），总计花费 10 元，总喜爱度 14。输出 14。

示例2：
输入:
6 7
3 1 8
4 1 2
3 1 1
9 1 7
4 1 1
5 1 8
4 1 4

输出:
9

说明:
6元可以购买两个3元的零食，喜爱度综合为8+1=9



dp[j] = max(dp[j], dp[j - cost] + fav)
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x, N;
    cin >> x >> N;

    vector<int> dp(x + 1, 0);

    for (int i = 0; i < N; i++) {
        int price, cnt, love;
        cin >> price >> cnt >> love;

        // 二进制拆分
        for (int k = 1; cnt > 0; k <<= 1) {
            int take = min(k, cnt);
            cnt -= take;

            int cost = price * take;
            int value = love * take;

            // 01 背包
            for (int j = x; j >= cost; j--) {
                dp[j] = max(dp[j], dp[j - cost] + value);
            }
        }
    }

    cout << dp[x] << '\n';
    return 0;
}
