//
// Created by Krisw on 2025/12/26.
//

/*
题目描述
给你一个整数M和数组N，N中的元素为连续整数，要求根据N中的元素组装成新的数组R，组装规则:
1.R中元素总和加起来等于M
2.R中的元素可以从N中重复选取
3.R中的元素最多只能有1个不在N中，且比N中的数字都要小(不能为负数)
输入描述
第一行输入是连续数组N，采用空格分隔第二行输入数字M
输出描述
输出的是组装办法数量，int类型

备注
1≤M≤30
1 ≤ N.length ≤ 1000


示例1
输入
2
5

输出

1

说明
只有1种组装办法，就是[2,2,1]

示例2
输入
2 3
5
输出
2

说明
共两种组装办法，分别是[2,2,1]，[2,3]
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

int m;
int n;
int ans = 0;
int minNum = 0x3f3f3f;

vector<vector<int>> result;
vector<int> path;

vector<int> parseArray(const string& line) {
    vector<int> res;
    stringstream ss(line);
    string item;
    while (getline(ss, item, ' ')) {
        int x = stoi(item);
        res.push_back(x);
        minNum = min(minNum, x);
    }
    return res;
}

void backtracking(const vector<int>& nums, int curSum, int startIdx) {
    if (curSum == m) {
        result.push_back(path);
        ans++;
        return;
    }

    int rest = m - curSum;

    if (rest < minNum) {
        path.push_back(rest);
        result.push_back(path);
        ans++;
        path.pop_back();
        return;
    }

    for (int i = startIdx; i < n; i++) { // 允许重复和去重
        if (curSum + nums[i] > m) continue;
        path.push_back(nums[i]);
        backtracking(nums, curSum + nums[i], i);
        path.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    getline(cin, line);
    auto array = parseArray(line);

    sort(array.begin(), array.end());  // 保证组合有序
    n = array.size();

    cin >> m;

    backtracking(array, 0, 0);

    cout << ans << "\n";

    return 0;
}

