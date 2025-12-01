//
// Created by Krisw on 2025/11/30.
//
/*
某个打印机根据打印队列执行打印任务。打印任务分为九个优先级，分别用数字1-9表示，数字越大优先级越高。打印机每次从队列头部取出第一个任务A，
然后检查队列余下任务中有没有比A优先级更高的任务，如果有比A优先级高的任务，则将任务A放到队列尾部，否则就执行任务A的打印。
请编写一个程序，根据输入的打印队列，输出实际的打印顺序。
输入描述

输入一行，为每个任务的优先级，优先级之间用逗号隔开，优先级取值范围是1~9。
输出描述

输出一行，为每个任务的打印顺序，打印顺序从0开始，用逗号隔开
示例 1 输入输出示例仅供调试，后台判题数据一般不包含示例

输入

9,3,5

输出

0,2,1

说明

队列头部任务的优先级为9，最先打印，故序号为0；
接着队列头部任务优先级为3，队列中还有优先级为5的任务，优先级3任务被移到队列尾部；
接着打印优先级为5的任务，故其序号为1；
最后优先级为3的任务的序号为2。
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    getline(cin, line);

    vector<int> taskPriority;
    string tmp;
    for (const char c : line) {
        if (c == ',') {
            taskPriority.push_back(stoi(tmp));
            tmp.clear();
        } else {
            tmp.push_back(c);
        }
    }
    if (!tmp.empty()) taskPriority.push_back(stoi(tmp));

    // 得到一个从高到低排序的优先级列表
    vector<int> sortedPri = taskPriority;
    sort(sortedPri.begin(), sortedPri.end(), greater<int>());

    queue<pair<int, int>> q;
    int N = taskPriority.size();
    for (int i = 0; i < N; i++) { q.push({taskPriority[i], i}); }

    vector<int> printSeq;   // 第 k 次打印的是哪个任务的 idx
    printSeq.reserve(N);

    int pos = 0; // 指向当前应打印的最高优先级 sorted[pos]

    while (!q.empty()) {
        auto [pri, idx] = q.front();
        q.pop();

        if (pri == sortedPri[pos]) {
            printSeq.push_back(idx); // 记录“本次打印的是哪个任务”
            pos++;
        } else {             // 还有更高优先级任务，放回队尾
            q.push({pri, idx});
        }
    }

    // 现在 printSeq[0..n-1] 是按打印时间排序的任务下标
    // 反推每个任务被打印的“次序编号”
    vector<int> ans(N);
    for (int i = 0; i < N; ++i) {
        int taskIdx = printSeq[i];  // 第 i 次打印的是 taskIdx
        ans[taskIdx] = i;        // 所以该任务的打印顺序是 i
    }

    for (int i = 0; i < N; ++i) {
        if (i) cout << ",";
        cout << ans[i];
    }
    cout << "\n";
}
