//
// Created by Krisw on 2026/1/18.
//

/*
现有N个任务需要处理，同一时间只能处理一个任务，处理每个任务所需要的时间固定为1。
每个任务都有最晚处理时间限制和积分值，在最晚处理时间点之前处理完成任务才可获得对应的积分奖励。
可用于处理任务的时间有限，请问在有限的时间内，可获得的最多积分。

输入描述

第一行为一个数N，表示有N个任务，1<=N<=100
第二行为一个数T，表示可用于处理任务的时间。1<=T<=100
接下来N行，每行两个空格分隔的整数(SLA和V)，SLA表示任务的最晚处理时间，V表示任务对应的积分。1<=SLA<=100, 0<=V<=100000

输出描述

可获得的最多积分

示例1

输入

4
3
1 2
1 3
1 4
1 5

输出

5

说明

虽然有3个单位的时间用于处理任务，可是所有任务在时刻1之后都无效。
所以在第1个时间单位内，选择处理有5个积分的任务。1-3时无任务处理。

示例2

输入

4
3
1 2
1 3
1 4
3 5

输出

9

说明

第1个时间单位内，处理任务3，获得4个积分

第2个时间单位内，处理任务4，获得5个积分

第3个时间单位内，无任务可处理

共获得9个积分
 */

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct Task {
    int sla;
    int val;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, T;
    cin >> N;
    cin >> T;

    vector<Task> tasks(N);
    for (int i = 0; i < N; i++) {
        cin >> tasks[i].sla >> tasks[i].val;
    }

    // 按截止时间升序
    sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return a.sla < b.sla;
    });

    priority_queue<int, vector<int>, greater<int>> minHeap;

    for (auto &task : tasks) {
        int limit = min(task.sla, T);

        if (static_cast<int>(minHeap.size()) < limit) {
            minHeap.push(task.val);
        } else if (!minHeap.empty() && minHeap.top() < task.val) {
            minHeap.pop();
            minHeap.push(task.val);
        }
    }

    long long ans = 0;
    while (!minHeap.empty()) {
        ans += minHeap.top();
        minHeap.pop();
    }

    cout << ans << "\n";
    return 0;
}
