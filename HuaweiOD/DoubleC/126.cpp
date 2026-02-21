//
// Created by Krisw on 2026/1/28.
//

/*
给定 str1 和 str2，如果 str1的字符串排列组合能在 str2 里面找到，则返回 str2 第一个匹配的字符的下标。如 str1 = “abc”，str2 = “qwcab” 返回 2；str1 = “abc”，str2 = “qcwab” 返回 -1。

示例1

输入：abc qwcab

输出：2

示例2

输入：abc qcwab

输出：-1
*/

#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string str1, str2;
    if (!(cin >> str1 >> str2)) return 0;

    int n = (int)str1.size(), m = (int)str2.size();
    if (n > m) {
        cout << -1 << "\n";
        return 0;
    }

    // need[c] 表示窗口里还需要多少个字符 c 才能匹配
    vector<int> need(256, 0);
    for (unsigned char c : str1) need[c]++;

    int missing = n; // 还差多少个字符匹配（计数意义）
    int l = 0;

    for (int r = 0; r < m; r++) {
        unsigned char cr = (unsigned char)str2[r];

        // 把 cr 纳入窗口：如果 need[cr] > 0，说明这是我们需要的字符
        if (need[cr] > 0) missing--;
        need[cr]--;

        // 保持窗口长度为 n
        if (r - l + 1 > n) {
            unsigned char cl = (unsigned char)str2[l];
            // 把 cl 移出窗口：need[cl]++，如果移出后 need[cl] > 0，说明少了一个需要的字符
            need[cl]++;
            if (need[cl] > 0) missing++;
            l++;
        }

        // 当窗口长度刚好为 n 且 missing==0，说明窗口字符计数与 str1 完全匹配
        if (r - l + 1 == n && missing == 0) {
            cout << l << "\n";
            return 0;
        }
    }

    cout << -1 << "\n";
    return 0;
}
