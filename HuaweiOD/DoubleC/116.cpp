//
// Created by Krisw on 2026/1/17.
//

/*
有 M(1<=M<=10) 个端口组
每个端口组是长度为 N(1<=N<=100)的整数数组，如果端口组间存在2个及以上不同端口相同，则认为这2个端口组 互相关联，可以合并
第一行输入端口组个数M，再输入M行，每行逗号分隔，代表端口组。输出合并后的端口组，用二维数组表示
输入描述
第一行输入一个数字M
第二行开始输入M行，每行是长度为N的整数数组，用逗号分割

输出描述
合并后的二维数组，用二维数组表示

1：组合内同端口仅保留一个，并从小到大排序。

2：组合外顺序保持输入顺序。

示例1：

输入：

4
4
2,3,2
1,2
5

输出：

[[4],[2,3],[1,2],[5]]

示例2：

输入：

3
2,3,1
4,3,2
5

输出：

[[1,2,3,4],[5]]

示例3：

输入：

6
10
4,2,1
9
3,6,9,2
6,3,4
8

输出：

[[10],[1,2,3,4,6,9],[9],[8]]
*/

#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;

vector<int> parseArray(const std::string &line, char delim) {
    stringstream ss(line);
    vector<int> array;
    string item;
    while (getline(ss, item, delim)) {
        array.push_back(stoi(item));
    }
    return array;
}

bool check(const set<int>& a, const set<int>& b) {
    int cnt = 0;
    auto it1 = a.begin();
    auto it2 = b.begin();

    while (it1 != a.end() && it2 != b.end()) {
        if (*it1 == *it2) {
            cnt++;
            if (cnt >= 2) return true;
            ++it1; ++it2;
        } else if (*it1 < *it2) {
            ++it1;
        } else {
            ++it2;
        }
    }
    return false;
}

bool merge(vector<set<int>>& ranges) {
    for (int i = 0; i < ranges.size(); i++) {
        for (int j = i + 1; j < ranges.size(); j++) {
            if (check(ranges[i], ranges[j])) {
                ranges[i].insert(ranges[j].begin(), ranges[j].end());
                ranges.erase(ranges.begin() + j);
                return true;
            }
        }
    }
    return false;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    cin >> M;
    cin.ignore();

    vector<set<int>> ranges;
    for (int i = 0; i < M; i++) {
        string line;
        getline(cin, line);
        auto array = parseArray(line, ',');
        ranges.push_back(set<int>(array.begin(), array.end()));
    }

    while (true) {
        if (!merge(ranges)) break;
    }

    cout << "[";
    for (int i = 0; i < ranges.size(); i++) {
        cout << "[";
        bool first = true;
        for (const auto x : ranges[i]) {
            if (!first) cout << ",";
            first = false;
            cout << x;
        }
        cout << "]";
        if (i != ranges.size() - 1) cout << ",";
    }
    cout << "]";

    return 0;
}