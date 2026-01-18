//
// Created by Krisw on 2026/1/18.
//

/*
游戏规则：输入一个只包含英文字母的字符串，字符串中的两个字母如果相邻且相同，就可以消除。
在字符串上反复执行消除的动作，直到无法继续消除为止，此时游戏结束。
输出最终得到的字符串长度。
输入描述:

输入原始字符串 str ，只能包含大小写英文字母，字母的大小写敏感， str 长度不超过100。
输出描述:

输出游戏结束后，最终得到的字符串长度。
示例1 输入输出示例仅供调试，后台判题数据一般不包含示例

输入

gg

输出

0

说明

gg 可以直接消除，得到空串，长度为0。

示例2 输入输出示例仅供调试，后台判题数据一般不包含示例

输入

mMbccbc

输出

3

说明

在 mMbccbc 中，可以先消除 cc ；

此时字符串变成 mMbbc ，可以再消除 bb ；

此时字符串变成 mMc ，此时没有相邻且相同的字符，无法继续消除。

最终得到的字符串为 mMc ，长度为3。

备注:

输入中包含 非大小写英文字母 时，均为异常输入，直接返回 0。
*/

#include <iostream>
#include <stack>
#include <cctype>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    getline(cin, s);

    if (s.empty()) {
        cout << 0 << '\n';
        return 0;
    }

    stack<char> st;
    for (char c : s) {
        if (!isalpha(static_cast<unsigned char>(c))) {
            cout << 0 << '\n';
            return 0;
        }
        if (!st.empty() && st.top() == c) {
            st.pop();      // 相邻相同 -> 消除
        } else {
            st.push(c);
        }
    }

    cout << st.size() << '\n';
    return 0;
}

// // 全部消除
// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//
//     string s;
//     getline(cin, s);
//
//     if (s.empty()) {
//         cout << 0 << '\n';
//         return 0;
//     }
//
//     // 输入合法性校验
//     for (char c : s) {
//         if (!isalpha(static_cast<unsigned char>(c))) {
//             cout << 0 << '\n';
//             return 0;
//         }
//     }
//
//     vector<pair<char,int>> st; // {字符, 连续次数}
//
//     for (char c : s) {
//         if (!st.empty() && st.back().first == c) {
//             st.back().second++;
//         } else {
//             st.push_back({c, 1});
//         }
//
//         // 达到 2 个立即整段消除
//         if (!st.empty() && st.back().second >= 2) {
//             st.pop_back();
//         }
//     }
//
//     // 统计剩余长度
//     int ans = 0;
//     for (auto &p : st) {
//         ans += p.second;
//     }
//
//     cout << ans << '\n';
//     return 0;
// }
