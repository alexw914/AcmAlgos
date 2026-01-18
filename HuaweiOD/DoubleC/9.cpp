//
// Created by Krisw on 2025/12/9.
//

/*
题目描述

有5台打印机打印文件，每台打印机有自己的待打印队列。因为打印的文件内容有轻重缓急之分，

所以队列中的文件有1~10不同的代先级，其中数字越大优先级越高。

打印机会从自己的待打印队列中选择优先级最高的文件来打印。

如果存在两个优先级一样的文件，则选择最早进入队列的那个文件。

现在请你来模拟这5台打印机的打印过程。

输入描述

每个输入包含1个测试用例，每个测试用例第一行给出发生事件的数量N（0 < N < 1000）。
接下来有 N 行，分别表示发生的事件。
共有如下两种事件：
1. “IN P NUM”，表示有一个拥有优先级 NUM 的文件放到了打印机 P 的待打印队列中。（0< P <= 5, 0 < NUM <= 10)；
2. “OUT P”，表示打印机 P 进行了一次文件打印，同时该文件从待打印队列中取出。（0 < P <= 5）。

输出描述

对于每个测试用例，每次”OUT P”事件，请在一行中输出文件的编号。
如果此时没有文件可以打印，请输出”NULL“。
文件的编号定义为”IN P NUM”事件发生第 x 次，此处待打印文件的编号为x。编号从1开始。

示例1   输入输出示例仅供调试，后台判断数据一般不包含示例

输入

7
IN 1 1
IN 1 2
IN 1 3
IN 2 1
OUT 1
OUT 2
OUT 2

输出

3
4
NULL
 */

#include <bits/stdc++.h>
#include <climits>
using namespace std;

struct TaskInfo {
    int pri;    // 优先级 (NUM)
    int seq;    // 进入队列的全局顺序（IN 第几次发生）
    int id;     // 文件编号（题目要求输出的 x，直接等于 seq）
};

// 比较器：返回 true 表示 a 的优先级“比 b 低”，堆会把“大的”放在 top
struct TaskCompare {
    bool operator()(const TaskInfo& a, const TaskInfo& b) const {
        if (a.pri != b.pri) {
            // 优先级高的应该排在前面 => pri 大的在 top
            return a.pri < b.pri;   // pri 小的“更小”，放下面
        }
        // 优先级相同，进入队列早的排在前面 => seq 小的在 top
        return a.seq > b.seq;       // seq 大的“更小”
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N = 0;
    cin >> N;

    priority_queue<TaskInfo, vector<TaskInfo>, TaskCompare> pq[6];
    int inCount = 0;  // “IN” 事件计数，同时也是文件编号 id

    for (int i = 0; i < N; ++i) {
        string op;
        cin >> op;
        if (op == "IN") {
            int P, NUM;
            cin >> P >> NUM;
            ++inCount;
            TaskInfo j{NUM, inCount, inCount};
            pq[P].push(j);
        } else if (op == "OUT") {
            int P;
            cin >> P;
            if (pq[P].empty()) {
                cout << "NULL\n";
            } else {
                TaskInfo j = pq[P].top();
                pq[P].pop();
                cout << j.id << "\n";
            }
        }
    }

    return 0;
}
