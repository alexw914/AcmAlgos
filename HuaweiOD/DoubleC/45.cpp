//
// Created by Krisw on 2025/12/15.
//

/*
一、题目

输入一个长度为4的倍数的字符串，字符串中仅包含WASD四个字母。

将这个字符串中的连续子串用同等长度的仅包含WASD的字符串替换，如果替换后整个字符串中WASD四个字母出现的频数相同，
那么我们称替换后的字符串是“完美走位”。

求子串的最小长度。

如果输入字符串已经平衡则输出0。

二、输入
一行字符表示给定的字符串s

数据范围：
1<=n<=10^5且n是4的倍数，字符串中仅包含WASD四个字母。

三、输出
一个整数表示答案

四、样例输入输出

示例1：

输入：
WASDAASD

输出：
1

说明：
将第二个A替换为W，即可得到完美走位 。

示例2：

输入：
AAAA

输出：
3

说明：
将其中三个连续的A替换为WSD，即可得到完美走位
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string str;
    cin >> str;

    const int N = str.size();
    unordered_map<char, int> cntMap;
    for (auto c: str) { cntMap[c]++; }

    if (cntMap['W'] == N / 4 && cntMap['A'] == N / 4 && cntMap['S'] == N / 4 && cntMap['D'] == N / 4) {
        cout << 0 << endl;
        return 0;
    }

    int l = 0, r = 0;
    int ans = N;
    while (r < N) {
        cntMap[str[r]]--;
        while (l <= r && cntMap['W'] <= N / 4 && cntMap['A'] <= N / 4 && cntMap['S'] <= N / 4 && cntMap['D'] <= N / 4) {
            ans = min(ans, r - l + 1);
            cntMap[str[l]]++;
            l++;
        }
        r++;
    }

    cout << ans << endl;
    return 0;
}
