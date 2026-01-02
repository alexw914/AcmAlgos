//
// Created by Krisw on 2025/12/8.
//
/*
服务之间交换的接口成功率作为服务调用关键质量特性，某个时间段内的接口失败率使用一个数组表示，

数组中每个元素都是单位时间内失败率数值，数组中的数值为0~100的整数，

给定一个数值(minAverageLost)表示某个时间段内平均失败率容忍值，即平均失败率小于等于minAverageLost，

找出数组中最长时间段，如果未找到则直接返回NULL。

输入描述

输入有两行内容，第一行为{minAverageLost}，第二行为{数组}，数组元素通过空格(” “)分隔，

minAverageLost及数组中元素取值范围为0~100的整数，数组元素的个数不会超过100个。

输出描述

找出平均值小于等于minAverageLost的最长时间段，输出数组下标对，格式{beginIndex}-{endIndx}(下标从0开始)，

如果同时存在多个最长时间段，则输出多个下标对且下标对之间使用空格(” “)拼接，多个下标对按下标从小到大排序。

示例1 输入输出示例仅供调试，后台判题数据一般不包含示例

输入

1

0 1 2 3 4

输出

0-2

说明

输入解释：minAverageLost=1，数组[0, 1, 2, 3, 4]

前3个元素的平均值为1，因此数组第一个至第三个数组下标，即0-2
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int minAvgLost;
    cin >> minAvgLost;

    string line;

    vector<int> lost;
    if (getline(cin, line)) {
        stringstream ss(line);
        vector<int> a;
        int x;
        while (ss >> x) {
            lost.push_back(x);
        }
    }

    const int N = lost.size();
    vector<int> prefix(N + 1, 0);
    for (int i = 0; i < N; ++i) {
        prefix[i + 1] = prefix[i] + lost[i];
    }

    int bestLen = 0;
    vector<pair<int, int>> ans;

    // 枚举所有区间 [i, j]
    for (int i = 0; i < N; ++i) {
        for (int j = i; j < N; ++j) {
            int total = prefix[j + 1] - prefix[i];
            int len = j - i + 1;
            // 平均值 <= minAverageLost  ⇔  total <= minAverageLost * len
            if (total <= minAvgLost * len) {
                if (len > bestLen) {
                    bestLen = len;
                    ans.clear();
                    ans.emplace_back(i, j);
                } else if (len == bestLen && len > 0) {
                    ans.emplace_back(i, j);
                }
            }
        }
    }

    if (bestLen == 0) {
        cout << "NULL";
        return 0;
    }

    sort(ans.begin(), ans.end());

    for (size_t k = 0; k < ans.size(); ++k) {
        if (k > 0) cout << ' ';
        cout << ans[k].first << '-' << ans[k].second;
    }

    return 0;
}
