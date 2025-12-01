//
// Created by Krisw on 2025/11/29.
//

/*
题目描述： 给定一个url前缀和url后缀,通过,分割 需要将其连接为一个完整的url
如果前缀结尾和后缀开头都没有/，需要自动补上/连接符 如果前缀结尾和后缀开头都为/，
需要自动去重 约束：不用考虑前后缀URL不合法情况 输入描述:
url前缀(一个长度小于100的字符串) url后缀(一个长度小于100的字符串)

输出描述： 拼接后的url

示例 1：

输入 /acm,/bb 输出 /acm/bb

示例 2：

输入 /abc/,/bcd 输出 /abc/bcd

示例 3：

输入 /acd,bef 输出 /acd/bef

示例 4：

输入 , 输出 /

*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    if (!getline(cin, line)) return 0;

    size_t pos = line.find(',');
    string pre, suf;
    if (pos == string::npos) {
        pre = line;
    } else {
        pre = line.substr(0, pos);
        suf = line.substr(pos + 1);
    }

    if (pre.empty() && suf.empty()) {
        cout << "/" << "\n";
        return 0;
    }

    if (!pre.empty() && suf.empty()) {
        if (pre.back() == '/') {
            cout << pre << "\n";
        } else {
            cout << pre << "/" << "\n";
        }
        return 0;
    }

    if (pre.empty() && !suf.empty()) {
        if (suf[0] == '/') {
            cout << suf << "\n";
        } else {
            cout << "/" << suf << "\n";
        }
        return 0;
    }

    bool preEndSlash = (pre.back() == '/');
    bool sufStartSlash = (suf[0] == '/');
    if (preEndSlash && sufStartSlash) {
        cout << pre << suf.substr(1) << "\n";
    } else if (!preEndSlash && !sufStartSlash) {
        cout << pre << "/" << suf << "\n";
    } else {
        cout << pre << suf << "\n";
    }

    return 0;
}