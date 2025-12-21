//
// Created by Krisw on 2025/12/18.
//

/*
疫情期间需要大家保证一定的社交距离，公司组织开交流会议。座位一排共 N 个座位，编号分别为[0,N-1],

要求员工一个接着一个进入会议室，并且可以在任何时候离开会议室。

满足：

每当一个员工进入时，需要坐到最大社交距离（最大化自己和其他人的距离的座位）；

如果有多个这样的座位，则坐到索引最小的那个座位。

输入描述

会议室座位总数seatNum。(1 <= seatNum <= 500)

员工的进出顺序 seatOrLeave 数组，元素值为 1，表示进场；元素值为负数，表示出场（特殊：位置 0 的员工不会离开）。

例如 -4 表示坐在位置 4 的员工离开（保证有员工坐在该座位上）

输出描述

最后进来员工，他会坐在第几个位置，如果位置已满，则输出-1。

示例1   输入输出示例仅供调试，后台判题数据一般不包含示例

输入

10
[1,1,1,1,-4,1]

输出

5

说明

seat -> 0,空在任何位置都行，但是要给他安排索引最小的位置，也就是座位 0
seat -> 9,要和旁边的人距离最远，也就是座位 9
seat -> 4,要和旁边的人距离最远，应该坐到中间，也就是座位 4
seat -> 2,员工最后坐在 2 号座位上
leave[4], 4 号座位的员工离开
seat -> 5,员工最后坐在 5 号座位上
*/

#include <bits/stdc++.h>
using namespace std;

int pickSeat(const set<int>& seats, int N) {
    if (seats.empty()) return 0;

    int bestIdx = 0;
    int bestDist = *seats.begin();              // 选 0，距离到 first

    int prev = -1;
    for (int s : seats) {
        if (prev != -1) {
            int mid = (prev + s) / 2;           // 并列自动偏左 -> 索引更小
            int dist = min(mid - prev, s - mid);
            if (dist > bestDist || (dist == bestDist && mid < bestIdx)) {
                bestDist = dist;
                bestIdx = mid;
            }
        }
        prev = s;
    }

    int last = *seats.rbegin();
    int rightDist = (N - 1) - last;             // 选 N-1
    if (rightDist > bestDist || (rightDist == bestDist && (N - 1) < bestIdx)) {
        bestIdx = N - 1;
    }
    return bestIdx;
}

int main() {
    int N;
    cin >> N;
    string line;
    getline(cin, line); // 吃掉换行
    getline(cin, line);                         // like [1,1,1,-4,1]

    line = line.substr(1, line.size() - 2);
    vector<int> ops;
    string tmp;
    for (char c : line) {
        if (c == ',') { ops.push_back(stoi(tmp)); tmp.clear(); }
        else tmp.push_back(c);
    }
    if (!tmp.empty()) ops.push_back(stoi(tmp));

    set<int> seats;
    int lastIdx = 0;

    for (int x : ops) {
        if (x == 1) {
            if (seats.size() == N) { lastIdx = -1; continue; }
            int idx = pickSeat(seats, N);
            seats.insert(idx);
            lastIdx = idx;
        } else {
            seats.erase(-x);
        }
    }

    cout << lastIdx << "\n";
    return 0;
}
