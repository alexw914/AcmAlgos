//
// Created by Krisw on 2025/12/15.
//
/*
推荐多样性需要从多个列表中选择元素，一次性要返回N屏数据(窗口数量)，每屏展示K个元素(窗口大小)，选择策略
1.各个列表元素需要做穿插处理，即先从第一个列表中为每屏选择一元素，再从第二个列表中为每屏选择一个元素，依次类推

2.每个列表的元素尽量均分为N份，如果不够N个，也要全部分配完，比如下面的例子:

(1)从第一个列表中选择4条0 1 2 3，分别放到4个窗口中
(2)从第二个列表中选择4条10 11 12 13，分别放到4个窗口中
(3)从第三个列表中选择4条20 21 22 23，分别放到4个窗口
(4)再从第一个列表中选择4条4 5 6 7，分别放到4个窗口中
(5)再从第一个列表中选择，由于数量不足4条，取剩下的2条，放到窗1和窗口2(6)再从第二个列表中选择，
由于数量不足4条并且总的元素数达到窗口要求，取18 19放到窗口3和窗口4


输入描述
第一行输入为N，表示需要输出的窗口数量，取值范围[1,10]

第二行输入为K，表示每个窗口需要的元素数量Q，取值范用[1,100]之后的行数不定(行数取值范围[1,10]，表示每个列表输出的元素列表。
元素之间以空格分隔，已经过准序外理，每人列表输出的元素数量取值范围[1,100]

输出描述

输出元素列表，元素数量=窗口数量“窗口大小，元素之间以空格分隔，多个窗口合并为一个列表输出，参考样例:先输出窗口1的元素列表，
再输出窗口2的元素列表，再输出窗口3的元素列表，最后输出窗口4的元素列表


示例1
输入

4
7
0 1 2 3 4 5 6 7 8 9
10 11 12 13 14 15 16 17 18 19
20 21 22 23 24 25 26 27 28 29
输出

0 10 20 4 14 24 8 1 11 21 5 15 25 9 2 12 22 6 16 26 18 3 13 23 7 17 27 19
说明：

1.每个列表会保证元素数最满足窗口要求，不需要考虑元素不足情况
2.每个列表的元素已去重，不需要考虑元素重复情况
3.每个列表的元素列表均不为空，不需要考虑列表为空情况
4.每个列表的元素列表已经过排序处理，输出结果要保证不改变同一个列表的元素顺序
5.每个列表的元素数量可能是不同的
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    string line;
    getline(cin, line); // 吃掉K后面的换行

    const int L = 3; // 固定三行列表
    vector<vector<long long>> lists;
    for (int i = 0; i < L; ) {
        if (!getline(cin, line)) break; // 防止输入不足
        bool allspace = true;
        for (char c : line) if (!isspace((unsigned char)c)) { allspace = false; break; }
        if (allspace) continue;

        stringstream ss(line);
        vector<long long> a;
        long long x;
        while (ss >> x) a.push_back(x);
        if (!a.empty()) {
            lists.push_back(std::move(a));
            ++i;
        }
    }

    int M = (int)lists.size();
    vector<int> idx(M, 0);
    vector<vector<long long>> win(N);

    long long need_total = 1LL * N * K;
    long long total = 0;

    while (total < need_total) {
        bool progressed = false;
        for (int li = 0; li < M && total < need_total; ++li) {
            for (int w = 0; w < N && total < need_total; ++w) {
                if ((int)win[w].size() >= K) continue;
                if (idx[li] >= (int)lists[li].size()) continue;
                win[w].push_back(lists[li][idx[li]++]);
                ++total;
                progressed = true;
            }
        }
        if (!progressed) break; // 防死循环
    }

    bool first = true;
    for (int w = 0; w < N; ++w) {
        for (auto v : win[w]) {
            if (!first) cout << ' ';
            cout << v;
            first = false;
        }
    }
    cout << "\n";
    return 0;
}

