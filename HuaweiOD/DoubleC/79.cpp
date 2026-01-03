//
// Created by Krisw on 2026/1/3.
//

/*
中秋节，公司分月饼，m个员工，买了n个月饼，m<=n，每个员工至少分1个月饼，但可以分多个，单人份到最多月饼的个数为Max1，
单人分到第二多月饼的个数是Max2，Max1-Max2<=3,。同理，单人分到第n-1多月饼的个数是Max(n-1)，单人分到第n多月饼的个数是Max(n)，
Max(n-1)-Max(n)<=3。请问有多少种分月饼的方法？

输入描述：

第一行输入m n，表示m个员工，n个月饼，m<=n

输出描述：

输出有多少种月饼分法

示例1：

输入：

2 4

输出：

2

说明：

4 = 1+3 （和3+1算一种分法）

4 = 2+2
共两种方案
*/

#include <iostream>
#include <vector>
using namespace std;

long long res = 0;

void dfs(int u, long long sum, int down, int up, int m) {
    if (u == m) {
        if (sum == 0) {
            res++;
        }
        return;
    }

    int remain = m - u;           // 剩余要分的人数（包含当前）
    if (down > up) return;

    // 最小总需求 / 最大总可分
    long long minNeed = 1LL * down * remain;
    long long maxNeed = 1LL * up * remain;
    if (sum < minNeed || sum > maxNeed) {
        return; // 无解，剪枝
    }

    // 特化最后一个人：必须刚好拿完 sum
    if (remain == 1) {
        if (sum >= down && sum <= up) {
            res++;
        }
        return;
    }

    for (int i = down; i <= up; ++i) {
        long long nextSum = sum - i;
        int nextDown = i;
        int nextUp = (int)min(nextSum, (long long)i + 3);
        dfs(u + 1, nextSum, nextDown, nextUp, m);
    }
}

int main() {
    int m;
    long long n;
    cin >> m >> n;
    dfs(0, n, 1, (int)n, m);
    cout << res << '\n';
    return 0;
}