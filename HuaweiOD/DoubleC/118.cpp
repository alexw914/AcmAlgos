//
// Created by Krisw on 2026/1/18.
//

/*
题目描述
小明正在规划一个大型数据中心机房，为了使得机柜上的机器都能正常满负荷工作，需要确保在每个机柜边上至少要有一个电箱。
为了简化题目，假设这个机房是一整排，M表示机柜，I表示间隔，请你返回这整排机房，至少需要多少个电箱。如果无解请返回-1。
输入描述
第一行输入一个字符串，由 M 和 I 组成，表示机房的组成样式
输出描述
输出一个整数，表示整排机房至少需要多少个电箱。如果无解请返回-1。
示例1：
输入：

MIIM
输出：
2

*/

#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int n = s.size();
    int ans = 0;

    for (int i = 0; i < n; ++i) {
        if (s[i] == 'M') {
            // 优先放右边
            if (i + 1 < n && s[i + 1] == 'I') {
                ans++;
                i += 2; // 覆盖 i, i+1, i+2
            }
            // 否则放左边
            else if (i - 1 >= 0 && s[i - 1] == 'I') {
                ans++;
                // 只覆盖当前，继续往后
            }
            else {
                cout << -1 << '\n';
                return 0;
            }
        }
    }

    cout << ans << '\n';
    return 0;
}

/*
贪心策略

从左到右扫描：
当遇到一个 M 时：

优先在右侧放电箱（覆盖更远）
如果 i+1 == 'I' → 放在 i+1

否则尝试左侧
如果 i-1 == 'I' → 放在 i-1

否则 → 无解，返回 -1

放置后跳过已经被覆盖的位置。
*/