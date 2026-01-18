//
// Created by Krisw on 2026/1/18.
//

/*
书籍的长、宽都是整数对应 (l,w)。如果书A的长宽度都比B长宽大时，则允许将B排列放在A上面。现在有一组规格的书籍，书籍叠放时要求书籍不能做旋转，请计算最多能有多少个规格书籍能叠放在一起。

输入
[[20,16],[15,11],[10,10],[9,10]]
输出

3
解释：前三本可叠放在一起。
 */
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int> > parseArrays(string line, int cols) {
    for (char &c: line) {
        if (c == '[' || c == ']' || c == ',') c = ' ';
    }

    stringstream ss(line);
    vector<vector<int> > res;
    vector<int> cur;

    int x;
    while (ss >> x) { // 可以跳过一些两个空格的间隔
        cur.push_back(x);
        if (cur.size() == cols) {
            res.push_back(cur);
            cur.clear();
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    getline(cin, line);

    auto arrays = parseArrays(line, 2);

    if (arrays.empty()) {
        cout << 0 << '\n';
        return 0;
    }

    // 1. 排序：长度降序，宽度降序
    sort(arrays.begin(), arrays.end(), [](const auto &a, const auto &b) {
        if (a[0] != b[0]) return a[0] > b[0];
        return a[1] > b[1];
    });

    int n = arrays.size();
    vector<int> dp(n, 1);

    // 2. 二维严格递减 LIS
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (arrays[j][0] > arrays[i][0] && arrays[j][1] > arrays[i][1]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }

    int ans = *max_element(dp.begin(), dp.end());
    cout << ans << '\n';

    return 0;
}
