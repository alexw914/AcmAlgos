//
// Created by Krisw on 2026/1/15.
//

/*
在星球争霸篮球赛对抗赛中，最大的宇宙战队希望每个人都能拿到MVP，MVP的条件是单场最高分得分获得者。
可以并列所以宇宙战队决定在比赛中尽可能让更多队员上场，并且让所有得分的选手得分都相同，
然而比赛过程中的每1分钟的得分都只能由某一个人包揽。输出有得分的队员都是MVP时，最少得MVP得分。

输入描述

输入第一行为一个数字 t ，表示为有得分的分钟数 1 ≤ t ≤ 50
第二行为 t 个数字，代表每一分钟的得分 p， 1 ≤ p ≤ 50

输出描述

输出有得分的队员都是MVP时，最少得MVP得分。

示例1：

输入：

9
5 2 1 5 2 1 5 2 1

输出：

6
说明：

4人MVP，每个人都是6分。
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int t;
vector<int> p;
vector<bool> used;
int target;

bool dfs(int start, int curSum, int bucketLeft) {
    if (bucketLeft == 0) return true;
    if (curSum == target)
        return dfs(0, 0, bucketLeft - 1);

    int prev = -1;
    for (int i = start; i < t; i++) {
        if (used[i] || p[i] == prev) continue;
        if (curSum + p[i] > target) continue;

        used[i] = true;
        if (dfs(i + 1, curSum + p[i], bucketLeft)) return true;
        used[i] = false;

        prev = p[i];

        // 剪枝
        if (curSum == 0) break;
        if (curSum + p[i] == target) break;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t;
    p.resize(t);
    for (int i = 0; i < t; i++) cin >> p[i];

    int sum = accumulate(p.begin(), p.end(), 0);
    int mx = *max_element(p.begin(), p.end());

    sort(p.begin(), p.end(), greater<int>());

    for (int S = mx; S <= sum; S++) {
        if (sum % S != 0) continue;

        int k = sum / S;
        target = S;
        used.assign(t, false);

        if (dfs(0, 0, k)) {
            cout << S << "\n";
            return 0;
        }
    }

    // 理论上一定有解（至少 S = sum）
    cout << sum << "\n";
    return 0;
}
