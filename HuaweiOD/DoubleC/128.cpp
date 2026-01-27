//
// Created by Krisw on 2026/1/26.
//

/*
跳房子，也叫跳飞机，是一种世界性的儿童游戏
游戏参与者需要分多个回合按顺序跳到第1格直到房子的最后一格。
跳房子的过程中，可以向前跳，也可以向后跳。
假设房子的总格数是count，小红每回合可能连续跳的步教都放在数组steps中，请问数组中是否有一种步数的组合，可以让小红两个回合跳到最后一格?如果有，请输出索引和最小的步数组合.
注意:
数组中的步数可以重复，但数组中的元素不能重复使用
提供的数据保证存在满足题目要求的组合，且索引和最小的步数组合是唯一的
输入描述
第一行输入为房子总格数count，它是int整数类型。

第二行输入为每回合可能连续跳的步数，它是int整数数组类型
输出描述
返回索引和最小的满足要求的步数组合(顺序保持steps中原有顺序
备注
count ≤ 1000
0 ≤ steps.length ≤ 5000
-100000000 ≤steps ≤ 100000000

示例1：

输入

7
[1,4,5,2,2]
输出
[5, 2]

示例2：
输入

8
[-1,2,4,9,6]
输出

[-1, 9]
说明
此样例有多种组合满足两回合跳到最后，譬如: [-1,9]，[2,6]，其中[-1,9]的索引和为0+3=3，[2,6]的索和为1+4=5，所以索引和最小的步数组合[-1,9]
*/

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <sstream>
using namespace std;

vector<int> parseArray(const std::string& line, char delim) {
    stringstream ss(line);
    string item;
    vector<int> array;
    while (getline(ss, item, delim)) {
        array.push_back(stoi(item));
    }
    return array;
}


vector<int> steps;
int n;
int cnt;

vector<vector<int>> results;
vector<int> path;

void backtracking(int curSum, int startIdx) {
    if (path.size() > 2) return;

    if (curSum == cnt && path.size() == 2) {
        results.push_back(path);
        return;
    }

    for (int i = startIdx; i < n; i++) {
        path.push_back(i);
        backtracking(curSum + steps[i], i + 1);
        path.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> cnt;
    cin.ignore();

    string line;
    getline(cin, line);

    steps = parseArray(line.substr(1, line.size() - 2), ',');
    n = steps.size();

    backtracking(0, 0);
    sort(results.begin(), results.end(), [](vector<int>& a, vector<int>& b) {
        return accumulate(a.begin(), a.end(), 0) < accumulate(b.begin(), b.end(), 0);
    });

    cout << "[";
    for (int i = 0; i < results[0].size(); i++) {
        cout << steps[results[0][i]];
        if (i != results[0].size() - 1) cout << ',';
    }
    cout << "]\n";

    return 0;
}
