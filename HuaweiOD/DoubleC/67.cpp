//
// Created by Krisw on 2026/1/2.
//

/*
题目描述：

一个工厂有m条流水线，来并行完成n个独立的作业，该工厂设置了一个调度系统，在安排作业时，总是优先执行处理时间最短的作业。
现给定流水线个数m，需要完成的作业数n, 每个作业的处理时间分别为t1,t2…tn。请你编程计算处理完所有作业的耗时为多少？
当n>m时，首先处理时间短的m个作业进入流水线，其他的等待，当某个作业完成时，依次从剩余作业中取处理时间最短的进入处理。
输入描述：

第一行为2个整数（采用空格分隔），分别表示流水线个数m和作业数n
第二行输入n个整数（采用空格分隔），表示每个作业的处理时长t1,t2…tn。
0< m,n<100
0<t1,t2…tn<100
注：保证输入都是合法的。
输出描述：

输出处理完所有作业的总时长


示例

输入：

3 5
8 4 3 2 10
输出：

13
说明：

先安排时间为2、3、4的3个作业。
第一条流水线先完成作业，然后调度剩余时间最短的作业8。
第二条流水线完成作业，然后调度剩余时间最短的作业10。
总工耗时就是第二条流水线完成作业的时间13（3+10）。
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    vector<int> taskTime(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> taskTime[i];
    }

    sort(taskTime.begin(), taskTime.end());

    // 如果作业数不超过流水线数，最久的那个任务决定总耗时
    if (n <= m) {
        cout << taskTime.back() << "\n";
        return 0;
    }

    // 小根堆，存每条流水线当前的结束时间
    priority_queue<int, vector<int>, greater<int>> pq;

    // 先把最短的 m 个任务分给 m 条流水线
    for (int i = 0; i < m; ++i) { pq.push(taskTime[i]); }

    // 对剩余任务，分配给当前最早空闲的流水线
    for (int i = m; i < n; ++i) {
        int cur = pq.top(); pq.pop();   // 当前最早完成的流水线
        cur += taskTime[i];            // 把新任务加上去
        pq.push(cur);                  // 更新结束时间
    }

    // 堆里最大值就是总耗时
    int ans = 0;
    while (!pq.empty()) {
        ans = max(ans, pq.top());
        pq.pop();
    }

    cout << ans << "\n";

    return 0;
}