//
// Created by Krisw on 2025/12/3.
//

/*
小明有n个可选运动，每个运动有对应卡路里，想选出其中k个运动且卡路里和为t。k，t，n都是给定的。求出可行解数量
输入描述
第一行输入n t k
第二行输入 每个运动的卡路里 按照空格进行分割
备注
0<n<10
t>0，0<k<=n
每个运动量的卡路里>0
输出描述
求出可行解数量

示例1：

输入

4 3 2
1 1 2 3

输出

2

说明
可行解为2，选取{0,2},{1,2}两种方式。

类似题目可参考: https://leetcode.cn/problems/combinations/description/
 */

#include <bits/stdc++.h>
using namespace std;

int n, k, t;
vector<int> a;
int ans = 0;

vector<vector<int>> result;
vector<int> path;

void backtracking(int sum, int startIdx) {
    if (sum > t) return;

    if (path.size() == k) {
        if (sum == t) {
            result.push_back(path);
            ans++;
        }
        return;
    }

    for (int i = startIdx; i < n ; ++i) {
        sum += a[i];
        path.push_back(i);
        backtracking(sum, i + 1);
        sum -= a[i];
        path.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> t >> k;
    a.resize(n);
    for (int i = 0; i < n; ++i) { cin >> a[i]; }

    backtracking(0, 0);

    for (auto & r : result) {
        for (auto & i : r) {
            cout << i << ' ';
        }
        cout << endl;
    }

    cout << ans << "\n";
    return 0;
}
