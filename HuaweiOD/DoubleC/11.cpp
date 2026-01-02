//
// Created by Krisw on 2025/12/11.
//
/*
有一堆长方体积木，它们的高度和宽度都相同，但长度不一。

小橙想把这堆积木叠成一面墙，墙的每层可以放一个积木，也可以将两个积木拼接起来，要求每层的长度相同。

若必须用完这些积木，叠成的墙最多为多少层？

如下是叠成的一面墙的图示，积木仅按宽和高所在的面进行拼接。



输入描述：

输入为一行，为各个积木的长度，数字为正整数，并由空格分隔。积木的数量和长度都不超过5000。

输出描述：

输出一个数字，为墙的最大层数，如果无法按要求叠成每层长度一致的墙，则输出-1。

输入

给定积木的长度，以空格分隔，例如:3 6 6 3。

输出

如果可以搭建，返回最大层数，如果不可以返回-1。

示例1   输入输出示例仅供调试，后台判题数据一般不包含示例

输入

3 6 6 3

输出

3

解释：以 6 为底的墙，第一层为 6 ，第二层为 6，第三层 3 + 3。

示例2   输入输出示例仅供调试，后台判题数据一般不包含示例

输入

1 4 2 3 6

输出

-1

解释：

无法组成长度相同的结果

 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    vector<int> length;
    if (getline(cin, line)) {
        stringstream ss(line);
        int x;
        while (ss >> x) {
            length.push_back(x);
        }
    }

    sort(length.begin(), length.end());
    int N = length.size();
    if (N == 1) {
        cout << 1 << endl;
        return 0;
    }
    if (N == 2) {
        if (length[0] == length[1]) {
            cout << 2 << endl;
        } else { cout << 1 << endl; }
        return 0;
    }

    auto max_len = length[N - 1] + length[0];
    auto min_len = length[N - 1];

    bool found = false;

    // 只需要检查两个候选层长：min_len（最大积木）和 max_len（最小+最大）
    vector<int> candidates = {min_len, max_len};
    if (min_len == max_len) candidates.pop_back(); // 防止重复

    for (int len : candidates) {
        // length 已经是升序：[0 .. N-1]
        auto lb = lower_bound(length.begin(), length.end(), len); // 第一个 >= len
        auto ub = upper_bound(length.begin(), length.end(), len); // 第一个 > len

        int k = lb - length.begin();   // < len 的个数，对应下标 [0 .. k-1]
        int m = ub - length.begin();   // <= len 的末尾是 m-1

        int single = m - k;            // == len 的个数

        // 如果存在 > len 的积木（下标 >= m），这种 len 不可行
        if (ub != length.end()) continue;

        // < len 的必须两两配对
        if (k % 2 != 0) continue;

        int i = 0, j = k - 1;
        int pairs = 0;
        bool ok = true;

        while (i < j) {
            int s = length[i] + length[j];
            if (s == len) {
                ++pairs;
                ++i;
                --j;
            } else {
                ok = false;
                break;
            }
        }

        if (ok) {
            cout << single + pairs << "\n";
            return 0;
        }
    }
    cout << -1 << "\n";
    return 0;
}
