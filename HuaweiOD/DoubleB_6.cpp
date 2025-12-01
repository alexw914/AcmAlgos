//
// Created by Krisw on 2025/11/30.
//

/*
有一个荒岛，只有左右两个港口，只有一座桥连接这两个港口，现在有一群人需要从两个港口逃生，有的人往右逃生，有的往左逃生，如果两个人相遇，
则PK，体力值大的能够打赢体力值小的，体力值相同则同归干尽，赢的人才能继续往前逃生，并减少相应的体力
输入描述
一行非 0 整数，用空格隔开，正数代表向右逃生，负数代表向左逃生
输出描述
最终能够逃生的人数
示例1：
输入
5 10 8 -8 -5
输出

2
说明
8与-8 相遇，同归于尽，10 遇到-5，打赢并减少五点体力，最终逃生的为5，5，均从右侧港口逃生，输出2
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    stack<int> s;
    int n;
    while (cin >> n) {
        // 当前这个人还活着吗
        bool alive = true;

        if (n > 0) {
            // 向右走的人，只有前面向左的人才有可能相遇，
            // 但栈顶是“在它前面的人”，栈顶<0 说明在它左边还往左走，是背道而驰，不会碰
            s.push(n);
        } else {  // n < 0，向左
            // 只要栈顶是向右走的人，就可能相遇
            while (!s.empty() && s.top() > 0 && alive) {
                int top = s.top();
                int ans = top + n;  // n 为负数，相当于 top - |n|

                if (ans > 0) {
                    // 栈顶赢，减去 |n| 的体力
                    s.top() = ans;
                    alive = false;  // 当前的 n 死了
                } else if (ans < 0) {
                    // 当前的 n 赢，减去 top 的体力，继续和前面的人打
                    s.pop();
                    n = ans;  // 仍为负数，体力减少
                    // alive 仍为 true，继续 while
                } else {  // ans == 0，同归于尽
                    s.pop();
                    alive = false;
                }
            }

            // 如果一路打过去都没被打死，就入栈
            if (alive) { s.push(n); }
        }
        if (cin.peek() == '\n') break;  // 处理一行输入
    }
    cout << s.size() << endl;
    return 0;
}