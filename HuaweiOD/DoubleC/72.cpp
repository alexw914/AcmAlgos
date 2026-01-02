//
// Created by Krisw on 2025/12/27.
//

/*
小明和朋友玩跳格子游戏，有 n 个连续格子，每个格子有不同的分数，小朋友可以选择以任意格子起跳，但是不能跳连续的格子，也不能回头跳；

给定一个代表每个格子得分的非负整数数组，计算能够得到的最高分数。

输入描述：

给定一个数列，如: 1 2 3 1

1 ≤ nums.length ≤ 100

0 <= nums[i] <= 1000

输出描述：

输出能够得到的最高分，如: 4

示例1：

输入：

2 7 9 3 1

输出：

12

leetcode:打家劫舍(https://leetcode.cn/problems/house-robber/)
*/

#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

vector<int> parseArray(const string &line, char delim) {
    vector<int> array;
    stringstream ss(line);
    string item;
    while (getline(ss, item, delim)) {
        array.push_back(stoi(item));
    }
    return array;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    getline(cin, line);
    auto array = parseArray(line, ' ');

    const int N = array.size();
    vector<int> dp(N, 0);
    if (N == 0) {
        cout << 0 << endl;
        return 0;
    }
    if (N == 1) {
        cout << array[0] << endl;
        return 0;
    }

    dp[0] = array[0];
    dp[1] = max(array[0], array[1]);
    for (int i = 2; i < N; i++) {
        dp[i] = max(dp[i - 2] + array[i], dp[i - 1]);
    }

    cout << dp[N - 1] << endl;
    return 0;
}
