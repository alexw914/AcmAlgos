//
// Created by Krisw on 2025/11/30.
//
/*
一线运维人员在对通话流量进行监控，每一段时间内都是出现流量的高峰，流量有高有低形成一个个波峰波谷，
运维人员想找到流量变化最快的波峰，你可以帮助他吗?
给定一个整数数组nums，代表采样点的流量值，请找到满足以下条件的三元组(i.j,k):

其中i<j<k，nums[i]<nums[j]且nums[j]>nums[k](即j是峰顶)，并找到所有满足条件的三元组中(k-i)的最小值
输入描述
第一行为n个整数，表示数组中的n个元素，0<=n<=100000
输出描述
返回所有满足条件的三元组中(k-i)的 最小值。若不存在，返回-1。

示例1：

输入：

3 5 4 7 2 1

输出：

2

说明：

满足条件的三元组为[0, 1, 2],距离2


示例2：

输入：

4 3 2 1

输出：

-1

说明：

无法找到满足条件的三元组，返回-1
 */

#include <iostream>
#include <vector>
#include <sstream>
#include <stack>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    getline(cin, line);
    stringstream ss(line);

    vector<int> v;
    int x;
    while (ss >> x) v.push_back(x);

    int N = v.size();
    if (N < 3) {
        cout << -1 << "\n";
        return 0;
    }

    vector<int> left(N, -1);
    vector<int> right(N, -1);

    stack<int> stkLeft;
    for (int i = 0; i < N; i++) {
        while (!stkLeft.empty() && v[stkLeft.top()] >= v[i]) { stkLeft.pop(); }
        if (!stkLeft.empty()) left[i] = stkLeft.top();
        stkLeft.push(i);
    }

    stack<int> stkRight;
    for (int i = N - 1; i >= 0; i--) {
        while (!stkRight.empty() && v[stkRight.top()] >= v[i]) { stkRight.pop(); }
        if (!stkRight.empty()) right[i] = stkRight.top();
        stkRight.push(i);
    }

    int ans = INT_MAX;
    for (int j = 0; j < N; ++j) {
        if (left[j] != -1 && right[j] != -1) { ans = min(ans, right[j] - left[j]); }
    }

    if (ans == INT_MAX) ans = -1;
    cout << ans << "\n";
    return 0;
}