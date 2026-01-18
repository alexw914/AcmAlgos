//
// Created by Krisw on 2026/1/18.
//

/*
Alice最近迷上分弹珠游戏，每次从箱子里拿出随机数量的弹珠，第一次将弹珠分为尽可能相等的两份，(偶数平分，奇数则其中一份比另外一份多一颗)，
第二次将这两份弹珠各自再尽可能分为相等的两份，直到每份弹珠不超过2颗。
如果第一次取出弹珠就已经少于三颗，则不用分，你能在Alice取出弹珠后就知道它要分多少次，最终会分成多少份吗?
输入描述
一个整数N，表示Alice拿到的弹珠数。范围:0<N<131072
输出描述
输出分拆需要的次数，分拆完成后的分数，使用空格分割。
示例1
输入

1
输出
0 1
示例2
输入
11
输出
6 7
说明：
11 第一次拆分为5和6，第二次5拆分为2和3，第三次6拆分为两个3，每个3再拆分1次，共拆分6次，分为7份。
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    if (n < 3) {
        cout << "0 1" << endl;
        return 0;
    }

    queue<int> q;
    q.push(n);
    int split_cnt = 0;
    int split_part = 0;
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        if (cur < 3) {
            split_part++;
            continue;
        }
        auto s1 = cur / 2, s2 = cur - cur / 2;
        q.push(s1);
        q.push(s2);
        split_cnt++;
    }
    cout << split_cnt << " " << split_part << endl;
    return 0;
}
