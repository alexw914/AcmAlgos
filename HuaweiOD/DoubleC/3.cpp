//
// Created by Krisw on 2025/12/6.
//
/*
某公司部门需要派遣员工去国外做项目。
现在，代号为 x 的国家和代号为 y 的国家分别需要 cntx 名和 cnty 名员工
部门每个员工有一个员工号 (1,2,3,......)，工号连续，从 1开始。部长派遣员工的规则:
规则1: 从 1,k中选择员工派遣出去
规则2: 编号为 x的倍数的员工不能去 x国，编号为 y 的倍数的员工不能去y 国
问题
找到最小的k，使得可以将编号在 [1,k] 中的员工分配给 x 国和 y 国，且满足 x 国和 y 国的需求

输入描述
四个整数 x,y,cntx,cnty。
2 < x < y < 30000
x和y 一定是质数
1 < cntx, cnty < 10^9
 cntx + cnty < 10^9
输出描述
满足条件的最小的 k

示例1：

输入：

2 3 3 1

输出：

5

说明:

输入中：
2 表示国家代号 2
3 表示国家代号 3
3 表示国家 2 需要3 个人

1 表示国家 3 需要1个人

输出的5表示k最小为5
容斥原理
 */

#include <iostream>
using namespace std;
using LL = long long;

LL x, y, cntx, cnty;

bool ok(LL k) {
    LL X = k - k / x; // 能去 x 国的人 = 非 x 的倍数
    LL Y = k - k / y; // 能去 y 国的人 = 非 y 的倍数
    LL Z = k - k / x - k / y + k / (x * y);     // 能同时去两个国家（既不是 x 倍数也不是 y 倍数）

    if (X < cntx) return false;
    if (Y < cnty) return false;
    if (X + Y - Z < cntx + cnty) return false;

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> x >> y >> cntx >> cnty;
    LL L = 1, R = 1;
    while (!ok(R)) R *= 2;     // 初始右界扩张到足够大

    // 二分查找最小可行 k
    while (L < R) {
        LL mid = L + (R - L) / 2;
        if (ok(mid)) R = mid;
        else L = mid + 1;
    }

    cout << L << endl;
    return 0;
}

