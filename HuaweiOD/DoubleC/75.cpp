//
// Created by Krisw on 2026/1/3.
//

/*
给定一个正整数 n，如果能够分解为 m (m > 1) 个连续正整数之和，请输出所有分解中，m最小的分解。
如果给定整数无法分解为连续正整数，则输出字符串"N"。


输入描述
输入数据为一整数，范围为 (1,2^30]
输出描述
比如输入为:
21
输出:
21=10+11


示例1：
输入

21
输出
21=10+11
21可以分解的连续正整数组合的形式有多种
说明
21=1+2+3+4+5+6

21=6+7+8

21=10+11
其中 21=10+11，是最短的分解序列。

n=a+(a+1)+⋯+(a+m−1)
a = (2n / m - (m -1)) / 2
1. 2n整除m
2. 分子大于等于2 (正整数)
m从2递增，寻找到第一个a
*/

#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    bool found = false;
    int  best_m = 0, best_a = 0;

    // m 为连续项的个数，至少为 2
    for (int m = 2; m * (m + 1) / 2 <= n; ++m) {
        int numerator = 2 * n - m * (m - 1);  // = 2m * a

        if (numerator <= 0) continue;
        int denom = 2 * m;

        if (numerator % denom != 0) continue;       // a 不是整数

        int a = numerator / denom;
        if (a >= 1) {
            best_m = m;
            best_a = a;
            found = true;
            break;  // m 递增，第一个合法的就是 m 最小的
        }
    }

    if (!found) {
        cout << "N";
        return 0;
    }

    // 输出形如：21=10+11
    cout << n << '=';
    for (int i = 0; i < best_m; ++i) {
        if (i > 0) cout << '+';
        cout << (best_a + i);
    }
    return 0;
}
