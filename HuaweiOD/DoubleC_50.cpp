//
// Created by Krisw on 2025/12/24.
//

/*
现有一个CPU和一些任务需要处理，已提前获知每个任务的任务ID、优先级、所需执行时间和到达时间。
CPU同时只能运行一个任务，请编写一个任务调度程序，采用“可抢占优先权调度”调度算法进行任务调度，规则如下：
1：如果一个任务到来时，CPU是空闲的，则CPU可以运行该任务直到任务执行完毕。
但是如果运行中有一个更高优先级的任务到来，则CPU必须暂停当前任务去运行这个优先级更高的任务；
2：如果一个任务到来时，CPU正在运行一个比他优先级更高的任务时，信道大的任务必须等待；
3：当CPU空闲时，如果还有任务在等待，CPU会从这些任务中选择一个优先级最高的任务执行，相同优先级的任务选择到达时间最早的任务。
输入描述
输入有若干行，每一行有四个数字（均小于10^8）,分别为任务ID，任务优先级，执行时间和到达时间。每个任务的任务ID不同，优先级数字越大优先级越高，并且相同优先级的任务不会同时到达。
输入的任务已按照到达时间从小到大排序，并且保证在任何时间，处于等待的任务不超过10000个。
输出描述
按照任务执行结束的顺序，输出每个任务的任务ID和对应的结束时间。
示例一
输入

1 3 5 1
2 1 5 10
3 2 7 12
4 3 2 20
5 4 9 21
6 4 2 22
输出

1 6
3 19
5 30
6 32
4 33
2 35
 */

#include <bits/stdc++.h>
using namespace std;

struct Task {
    long long id, pr, rem, at, seq;
};

struct Cmp {
    bool operator()(const Task& a, const Task& b) const {
        if (a.pr != b.pr) return a.pr < b.pr;   // 优先级高的先
        if (a.at != b.at) return a.at > b.at;   // 到达早的先
        return a.seq > b.seq;                   // 再按输入顺序
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Task> in;
    long long id, pr, et, at;
    long long seq = 0;
    while (cin >> id >> pr >> et >> at) {
        in.push_back({id, pr, et, at, seq++});
    }
    int n = (int)in.size();
    if (n == 0) return 0;

    priority_queue<Task, vector<Task>, Cmp> pq;
    int idx = 0;
    long long t = 0;

    auto push_arrivals = [&](long long now) {
        while (idx < n && in[idx].at <= now) {
            pq.push(in[idx]);
            idx++;
        }
    };

    bool hasRun = false;
    Task cur;

    // 从第一条任务到达时间开始
    t = in[0].at;

    while (true) {
        // 退出条件：没有未来输入、没有运行任务、等待队列也空
        if (idx >= n && !hasRun && pq.empty()) break;

        // 先把当前时刻到达的任务入队
        push_arrivals(t);

        // 如果没有正在运行的任务，尝试从队列取；如果队列空就跳到下一到达时间
        if (!hasRun) {
            if (pq.empty()) {
                // 只能跳到下一任务到达时间
                if (idx < n) t = max(t, in[idx].at);
                continue;
            } else {
                cur = pq.top(); pq.pop();
                hasRun = true;
            }
        }

        // 计算下一到达与完成时间
        long long nextArrival = (idx < n ? in[idx].at : LLONG_MAX);
        long long finishTime  = t + cur.rem;

        if (nextArrival >= finishTime) {
            // 期间无新任务到达，直接完成
            t = finishTime;
            cout << cur.id << " " << t << "\n";
            hasRun = false;
        } else {
            // 先运行到 nextArrival
            cur.rem -= (nextArrival - t);
            t = nextArrival;

            // 把此刻到达的任务入队
            push_arrivals(t);

            // 判断是否抢占
            if (!pq.empty() && pq.top().pr > cur.pr) {
                pq.push(cur);
                cur = pq.top(); pq.pop();
                hasRun = true;
            }
        }
    }

    return 0;
}
