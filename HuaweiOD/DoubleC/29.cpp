//
// Created by Krisw on 2025/12/21.
//

/*
小明正在尝试一种新的牌游戏。游戏规则只如下:首先，小明拿到一张写有数字m的牌。 然后，他会拿到另外n张牌，上面分别写有不同的数字，
牌排成一排。小明的目标是从这排牌中找到一串连续的牌，这些牌上数字的总和可以被 m整除。你的任务是判断小明是否可以完成这个目标。
输入描述
第一行包含两个整数:n和 m。其中n是小明拿到的牌的数量(不包括写有 m 的牌)，m 是写在第一张牌上的数字。
第二行包含 n个整数，这些整数分别是n张牌上的数字，
输出描述
如果小明可以找到一个连续的牌串，这些牌上数字的和可以被 m 整除，输出“1"。如果找不到符合条件的牌串，输出"0”。

示例1

输入：

6 7
2 12 6 3 5 5

输出：

1

示例2

输入：

10 11
1 1 1 1 1 1 1 1 1 1

输出：

0
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    if (m == 0) {
        cout << 0 << "\n";
        return 0;
    }

    vector<int> cards(n + 1, 0);
    for (int i = 1; i <= n; i++) { cin >> cards[i]; }

    // 前缀和
    vector<int> prefix(n + 1, 0);
    prefix[0] = 0;
    for (int i = 1; i <= n; i++) {
        prefix[i] = prefix[i - 1] + cards[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            int sum = prefix[i] - prefix[j - 1];
            if ((sum % m + m) % m == 0) {
                cout << 1 << endl;
                return 0;
            }
        }
    }
    cout << 0 << endl;
    return 0;
}
