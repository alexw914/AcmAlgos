//
// Created by Krisw on 2026/1/24.
//

/*

有一组区间[a0，b0]，[a1，b1]，…（a，b表示起点，终点），区间有可能重叠、相邻，重叠或相邻则可以合并为更大的区间；

给定一组连接器[x1，x2，x3，…]（x表示连接器的最大可连接长度，即x>=gap），可用于将分离的区间连接起来，但两个分离区间之间只能使用1个连接器；

请编程实现使用连接器后，最少的区间数结果。

区间数量<10000，a,b均 <=10000
连接器梳理<10000；x <= 10000

输入描述

区间组：[1,10],[15,20],[18,30],[33，40]
连接器组：[5,4,3,2]

输出描述

1

说明：

合并后：[1,10],[15,30],[33,40]，使用5, 3两个连接器连接后只剩下 [1, 40]。

示例1 输入输出示例仅供调试，后台判题数据一般不包含示例

输入

[1,10],[15,20],[18,30],[33,40]
[5,4,3,2]

输出

1

说明

合并后：[1,10], [15,30], [33,40]，使用5, 3两个连接器连接后只剩下[1,40]。

 */

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

vector<vector<int>> parseArrays(string str) {
    for (auto& c: str) {
        if (c == '[' || c == ']' || c == ',') c = ' ';
    }

    stringstream ss(str);
    int x;
    vector<vector<int>> arrays;
    vector<int> array;
    while (ss >> x) {
        array.push_back(x);
        if (array.size() == 2) {
            arrays.push_back(array);
            array.clear();
        }
    }
    return arrays;
}

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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    getline(cin, line);
    auto intervals = parseArrays(line);

    getline(cin, line);
    auto connect = parseArray( line.substr(1, line.size() - 2),',');

    sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>&b) {
        if (a[0] != b[0]) return a[0] < b[0];
        return a[1] < b[1];
    });

    vector<vector<int>> merged;
    for (auto i = 0 ; i < intervals.size(); i++) {
        if (merged.empty()) {
            merged.push_back(intervals[i]);
            continue;
        }
        if (intervals[i][0] > merged.back()[1]) {
            merged.push_back(intervals[i]);
        } else {
            merged.back()[1] = max(intervals[i][1], merged.back()[1]);
        }
    }

    // 3. 计算 gap
    int n = merged.size();
    vector<int> gaps;
    for (int i = 1; i < n; ++i) {
        gaps.push_back(merged[i][0] - merged[i - 1][1]);
    }

    sort(gaps.begin(), gaps.end());
    sort(connect.begin(), connect.end());

    int i = 0, j = 0;
    int used = 0;

    while (i < gaps.size() && j < connect.size()) {
        if (connect[j] >= gaps[i]) {
            used++;
            i++;
            j++;
        } else {
            j++;
        }
    }

    cout << n - used << "\n";

    return 0;
}