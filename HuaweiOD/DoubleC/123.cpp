//
// Created by Krisw on 2026/1/24.
//

/*

题目描述
给定 M 个字符( a-z ) ，从中取出任意字符(每个字符只能用一次)拼接成长度为 N 的字符串，要求相同的字符不能相邻。

计算出给定的字符列表能拼接出多少种满足条件的字符串，输入非法或者无法拼接出满足条件的字符串则返回 0 。

输入描述
给定长度为 M 的字符列表和结果字符串的长度 N ，中间使用空格(" ")拼接。

0 < M < 30
0 < N ≤ 5
输出描述
输出满足条件的字符串个数。

示例1
输入：
abc 1

输出：
3

说明：
给定的字符为 abc ，结果字符申长度为 1 ，可以拼接成 a、b、c ，共 3 种。

示例2
输入：
dde 2

输出：
2

说明：
给定的字符为 dde ，果字符串长度为 2 ，可以拼接成 de、ed， 共 2 种。


*/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

string str;
int t;
int ans = 0;

vector<string> result;
string path;

void backtracking(string& s, vector<bool>& used) {
    if (path.size() == t) {
        result.push_back(path);
        ans++;
        return;
    }
    for (int i = 0; i < s.size(); i++) {
        if (i > 0 && s[i] == s[i - 1] && used[i - 1] == false) {
            continue;
        }

        if (used[i]) continue; // 已经使用
        if (!path.empty() && path.back() == s[i]) continue; // 相同的字符不能相邻

        used[i] = true;
        path.push_back(s[i]);
        backtracking(s, used);
        path.pop_back();
        used[i] = false;
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> str >> t;
    sort(str.begin(), str.end());
    vector<bool> used(str.size(), false);

    backtracking(str, used);
    cout << ans << endl;

    return 0;
}
