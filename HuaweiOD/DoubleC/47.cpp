//
// Created by Krisw on 2025/12/23.
//

/*
给定a-z，26个英文字母小写字符串组成的字符串A和B，
其中A可能存在重复字母，B不会存在重复字母，现从字符串A中按规则挑选一些字母可以组成字符串B挑选规则如下：
1：同一个位置的字母只能挑选一次，
2：被挑选字母的相对先后顺序不能被改变，
求最多可以同时从A中挑选多少组能组成B的字符串
输入描述
输入为2行，
第一行输入字符串a,第二行输入字符串b，行首行尾没有多余空格
输出描述
输出一行
包含一个数字表示最多可以同时从a中挑选多少组能组成b的字符串，行末没有多余空格
示例一
输入

badc
bac
输出

1

示例二
输入

badc
abc

输出

0

示例三
输入

bbadcac
bac

输出

2
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string A, B;
    getline(cin, A);
    getline(cin, B);

    // 记录 B 中每个字符的位置（B 无重复字母）
    vector<int> idxs(26, -1);
    for (int i = 0; i < (int)B.size(); i++) {
        idxs[B[i] - 'a'] = i;
    }

    // count[i]：已经匹配到 B[i] 的“组”的数量
    vector<int> count(B.size(), 0);

    for (char c : A) {
        int idx = idxs[c - 'a'];
        if (idx == -1) continue; // 不在B里

        // idx==0：开新组
        // count[idx] < count[idx-1]：说明有组可以从前一位推进到这一位
        if (idx == 0 || count[idx] < count[idx - 1]) {
            count[idx]++;
        }
    }

    cout << count.back() << "\n";
    return 0;
}
