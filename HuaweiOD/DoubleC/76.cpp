//
// Created by Krisw on 2026/1/3.
//

/*
部门在进行需求开发时需要进行人力安排。当前部门需要完成 N 个需求，需求用 requirements[i] 表示，requirements[i] 表示第 i 个需求的工作量大小，单位：人月。
这部分需求需要在 M 个月内完成开发，进行人力安排后每个月的人力是固定的。

目前要求每个月最多有 2 个需求开发，并且每个月需要完成的需求不能超过部门人力。请帮部门评估在满足需求开发进度的情况下，每个月需要的最小人力是多少？

输入描述
输入第一行为 M ，第二行为 requirements ，长度为N。

M 表示需要开发时间要求，requirements 表示每个需求工作量大小

N 为 requirements 长度。

1 ≤ N / 2 ≤ M ≤ N ≤ 10000，1 ≤ requirements[i]≤ 10^9

输出描述
对于每一组测试数据，输出部门需要人力需求，行末无多余的空格。

示例1：
输入
3
3 5 3 4
输出
6
说明

当选择人力为6时，2个需求量为3的工作可以在1个月里完成，其他2个工作各需要1个月完成。可以在3个月内完成所有需求。

当选择人力为5时，4个工作各需要1个月完成，一共需要4个月才能完成所有需求。

因此6是部门最小的人力需求。

*/

#include <bits/stdc++.h>
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

// 判断在给定人力 capacity 下，是否能在 M 个月内完成所有需求
bool canFinish(const vector<int>& req, int M, int capacity) {
    int i = 0;
    int j = req.size() - 1;
    int months = 0;

    while (i <= j) {
        if (i == j) {
            // 只剩一个需求
            if (req[j] > capacity) return false;  // 安全判断
            ++months;
            break;
        }
        if (req[i] + req[j] <= capacity) {
            // 小的 + 大的 放一起
            ++i;
            --j;
        } else {
            // 大的单独一个月
            --j;
        }
        ++months;
        if (months > M) return false;  // 提前剪枝
    }
    return months <= M;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    cin >> M;
    cin.ignore();

    string line;
    getline(cin, line);
    auto req = parseArray(line, ' ');

    int N = (int)req.size();
    if (N == 0) {
        cout << 0 << '\n';
        return 0;
    }

    sort(req.begin(), req.end());

    int low = req.back();              // 至少要能容纳最大需求
    int high;
    if (N == 1) { high = req[0]; }
    else { high = req[N - 1] + req[N - 2]; }  // 最大两项之和作为上界

    int ans = high;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (canFinish(req, M, mid)) {
            ans = mid;
            high = mid - 1;  // 尝试更小的人力
        } else {
            low = mid + 1;   // 需要更大的人力
        }
    }

    cout << ans << '\n';
    return 0;
}