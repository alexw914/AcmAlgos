//
// Created by Krisw on 2025/12/21.
//

/*
给你一个字符串str和整数k，返回满足以下条件的所有子字符串个数:
1.恰好包含k个字母。
2.数字0-9各出现至少一次。


输入描述
第一行字符串str (1≤ str.length≤ 100000),仅包含数字和小写字母

第二行为整数k(0≤k≤100000)


输出描述
输出一个整数，表示满足所有条件的子字符串的个数，
子字符串是字符串中连续的非空字符序列

示例1

输入：

a0123456789aa
1

输出：

2
*/

#include <bits/stdc++.h>
using namespace std;

static inline bool isDigit(char c) { return c >= '0' && c <= '9'; }
static inline bool isLetter(char c) { return c >= 'a' && c <= 'z'; }

int main() {
    string s;
    int k;
    getline(cin, s);
    cin >> k;

    int n = s.length();
    int ans = 0;

    // 使用滑动窗口方法
    for (int left = 0; left < n; left++) {
        // 初始化窗口状态
        vector<int> digitCount(10, 0); // 记录数字0-9的出现次数
        int letterCount = 0; // 记录字母的出现次数
        int validDigits = 0; // 记录有多少种不同数字已出现（0-9）

        // 扩展右边界
        for (int right = left; right < n; right++) {
            char ch = s[right];

            if (isDigit(ch)) {
                // 处理数字字符
                int digit = ch - '0';
                if (digitCount[digit] == 0) {
                    validDigits++; // 新出现的数字种类
                }
                digitCount[digit]++;
            } else {
                // 处理字母字符
                letterCount++;
            }

            // 检查当前窗口是否满足条件
            if (validDigits == 10 && letterCount == k) {
                ans++;
            }

            // 如果字母数量超过k，提前终止当前左边界的搜索
            if (letterCount > k) {
                break;
            }
        }
    }
    cout << ans << endl;

    return 0;
}


// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(nullptr);
//
//     string str;
//     int k;
//     cin >> str >> k;
//
//     const int N = str.length();
//
//     // 记录每个数字最后一次出现的位置
//     int last[10];
//     for (int i = 0; i < 10; i++) last[i] = -1;
//     int seenDigits = 0; // 出现过的数字种类数
//
//     // 两个左指针：维护“字母数 <= k”和“字母数 <= k-1”
//     int l1 = 0, l2 = 0;
//     int letters1 = 0, letters2 = 0;
//
//     long long ans = 0;
//
//     for (int r = 0; r < N; r++) {
//         char c = str[r];
//
//         // 更新数字信息
//         if (isDigit(c)) {
//             int d = c - '0';
//             if (last[d] == -1) seenDigits++;
//             last[d] = r;
//         }
//
//         // 扩展两个窗口的字母计数
//         if (isLetter(c)) {
//             letters1++;
//             letters2++;
//         }
//
//         // 收缩 l1，使 [l1..r] 字母数 <= k
//         while (letters1 > k) {
//             if (isLetter(str[l1])) letters1--;
//             l1++;
//         }
//
//         // 收缩 l2，使 [l2..r] 字母数 <= k-1
//         if (k - 1 < 0) {
//             // 字母数 <= -1 不可能，直接让区间为空
//             l2 = r + 1;
//             letters2 = 0; // 无所谓
//         } else {
//             while (letters2 > k - 1) {
//                 if (isLetter(str[l2])) letters2--;
//                 l2++;
//             }
//         }
//
//         // 必须 0-9 都出现过
//         if (seenDigits != 10) continue;
//
//         // 计算 minLast：10个数字最后出现位置的最小值
//         int minLast = last[0];
//         for (int d = 1; d < 10; d++) minLast = min(minLast, last[d]);
//
//         // 恰好 k 个字母的起点 L 在 [l1, l2-1]
//         // 数字全覆盖要求 L <= minLast
//         int low = l1;
//         int high = l2 - 1;
//         int up = min(high, minLast);
//
//         if (up >= low) ans += (long long)(up - low + 1);
//     }
//
//     cout << ans << "\n";
//     return 0;
// }
