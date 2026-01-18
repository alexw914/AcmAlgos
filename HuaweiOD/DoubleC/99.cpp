//
// Created by Krisw on 2026/1/18.
//

/*
现在你要竞选一个县的县长。你去对每一个选民进行了调查。你已经知道每一个人要选的人是谁，以及要花多少钱才能让这个人选你。
现在你想要花最少的钱使得你当上县长。你当选的条件是你的票数比任何一个其它候选人的多（严格的多，不能和他们中最多的相等）。请计算一下最少要花多少钱。

输入
单组测试数据。
第一行有一个整数 (1≤n≤10^5) ，表示这个县的选民数目。
接下来有 n 行，每一行有两个整数 ai 和 bi(0≤ai≤10^5;0≤bi≤10^4) ，表示第 i 个选民选的是第 ai 号候选人，想要让他选择自己就要花 bi 的钱。
你是 0 号候选人（所以，如果一个选民选你的话 ai 就是 0 ，这个时候bi 也肯定是 0 ）。

输出
输出一个整数表示花费的最少的钱。

示例1：

输入：

5
1 2
1 2
1 2
2 1
0 0

输出：

3
*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    unordered_map<int, vector<int>> voters;
    unordered_map<int, int> cnt;

    int cnt0 = 0;

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        if (a == 0) {
            cnt0++;
        } else {
            cnt[a]++;
            voters[a].push_back(b);
        }
    }

    // 为每个候选人建立小根堆（最便宜优先）
    unordered_map<int, priority_queue<int, vector<int>, greater<int>>> heaps;
    for (auto &p : voters) {
        for (int cost : p.second)
            heaps[p.first].push(cost);
    }

    // 大根堆：按票数排序
    priority_queue<pair<int,int>> pq;
    for (auto &p : cnt) {
        pq.push({p.second, p.first});
    }

    long long ans = 0;

    while (!pq.empty()) {
        auto [c, id] = pq.top();

        if (cnt0 > c) break;

        pq.pop();

        int price = heaps[id].top();
        heaps[id].pop();

        ans += price;

        cnt0++;
        cnt[id]--;

        pq.push({cnt[id], id});
    }

    cout << ans << "\n";
    return 0;
}
