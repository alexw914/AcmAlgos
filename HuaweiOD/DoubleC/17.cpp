//
// Created by Krisw on 2025/12/12.
//
/*
在 软件版本管理中，版本号由点分割的数字组成，例如 1.2.3 和 2.8。现在，你需要编写一个函数，计算两个版本号之间的可用版本号个数。
这里的可用版本号指的是所有满足 version1<x<version2的版本号x的个数。若 version1 >=version2 返回0.，
输入描述
输入两个字符串 version1和 version2，均遵循以下规定
1.版本号由数字和点组成，且至少包含一个数字,
2.点不会作为版本号的开头或结尾，也不会连续出现。
3.每个数字部分的数值忽略前导零(例如1.01和1.001视为相同)
4.两个字符串中间以英文逗号分割
输出描述
输出一个整数，表示可用版本号的个数。具体规则如下:
如果 version1 >= version2 ,返回0
否则，找到第一个不同的版本号段，假设在位置i，version1的该段值为v1，version2的该段值为v2。可用版本号的个数为v2-v1-1。
如果第一个不同段之后的版本段在version2中不全为0，则返回0.

示例1：

输入：

1.2,1.4

输出：

1

说明：

不同段中version1为2，version2 为4，4-2-1=1
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> SplitVersion(const string& s) {
    vector<int> a;
    string part;
    stringstream ss(s);
    while (getline(ss, part, '.')) {
        // 题目保证每段至少一个数字，所以不会是空
        a.push_back(stoi(part)); // 自动忽略前导零
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    getline(cin, line);

    string v1s, v2s;
    {
        stringstream ss(line);
        getline(ss, v1s, ',');
        getline(ss, v2s);
    }

    auto v1 = SplitVersion(v1s);
    auto v2 = SplitVersion(v2s);

    int n = max(v1.size(), v2.size());
    v1.resize(n, 0);
    v2.resize(n, 0);

    // 找第一个不同段
    int i = 0;
    while (i < n && v1[i] == v2[i]) i++;

    // 完全相同
    if (i == n) {
        cout << 0 << "\n";
        return 0;
    }

    // version1 >= version2 ?
    if (v1[i] > v2[i]) {
        cout << 0 << "\n";
        return 0;
    }

    // 检查 version2 在 i 后是否全为 0
    for (int j = i + 1; j < n; j++) {
        if (v2[j] != 0) {
            cout << 0 << "\n";
            return 0;
        }
    }

    // 题意公式
    auto ans = v2[i] - v1[i] - 1;
    cout << (ans > 0 ? ans : 0) << "\n";
    return 0;
}
