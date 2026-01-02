//
// Created by Krisw on 2026/1/1.
//

/*
小王在进行游戏大闯关，有一个关卡需要输入一个密码才能通过，密码获得的条件如下：

在一个密码本中，每一页都有一个由26个小写字母组成的若干位密码，每一页的密码不同，需要从这个密码本中寻找这样一个最长的密码，

从它的末尾开始依次去掉一位得到的新密码也在密码本中存在。

请输出符合要求的密码，如果有多个符合要求的密码，则返回字典序最大的密码。

若没有符合要求的密码，则返回空字符串。

输入描述

密码本由一个字符串数组组成，不同元素之间使用空格隔开，每一个元素代表密码本每一页的密码。

输出描述

一个字符串

示例1  输入输出示例仅供调试，后台判题数据一般不包含示例

输入

h he hel hell hello

输出

hello

示例2  输入输出示例仅供调试，后台判题数据一般不包含示例

输入

b ereddred bw bww bwwl bwwlm bwwln

输出

bwwln

*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_set>
using namespace std;

vector<string> parseArray(const string &line) {
    vector<string> array;
    stringstream ss(line);
    string item;
    while (getline(ss, item, ' ')) {
        array.push_back(item);
    }
    return array;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    getline(cin, line);
    auto passwds = parseArray(line);

    sort(passwds.begin(), passwds.end(), [](const string &a, const string &b) {
        if (a.size() != b.size()) return a.size() < b.size();
        return a < b;
    });

    // 排序后使用依次从最短的字符串添加
    unordered_set<string> st;
    for (auto &s: passwds) {
        if (s.size() == 1) {
            st.insert(s);
        } else {
            string prev = s.substr(0, s.size() - 1);
            if (st.find(prev) != st.end()) { st.insert(s); }
        }
    }

    string ans;
    for (const auto &s: st) {
        if (ans.empty() || s.size() > ans.size() || (s.size() == ans.size() && s > ans)) {
            ans = s;
        }
    }
    cout << ans << endl;
    return 0;
}
