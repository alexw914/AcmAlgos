//
// Created by Krisw on 2025/12/22.
//

/*
智能手机方便了我们生活的同时，也侵占了我们不少的时间。“手机App防沉迷系统”能够让我们每天合理地规划手机App使用时间，在正确的时间做正确的事。
它的大概原理是这样的:
1.在一天24小时内，可以注册每个App的允许使用时段
2.一个时间段只能使用一个App
3.App有优先级，数值越高，优先级越高。注册使用时段时，如果高优先级的App时间和低优先级的时段有冲突，则系统会自动注销低优先级的时段，
如果App的优先级相同，则后添加的App不能注册。
请编程实现，根据输入数据注册App，并根据输入的时间点，返回时间点使用的App名称，如果该时间点没有注册任何App，请返回字符串“NA”。
输入描述
第一行表示注册的App数量 N (N <100)
第二部分包括 N 行，每行表示一条App注册数据
最后一行输入一个时间点，程序即返回该时间点使用的App
2
App1 1 09:00 10:00
App2 2 11:00 11:30
09:30
数据说明如下:
1.N行注册数据以空格分隔，四项数依次表示: App名称、优先级、起始时间、结束时间
2.优先级1~5，数字越大，优先级越高
3.时间格式 HH:MM，小时和分钟都是两位，不足两位前面补0
4.起始时间需小于结束时间，否则注册不上
5.注册信息中的时间段包含起始时间点，不包含结束时间点
输出描述
输出一个字符串，表示App名称，或NA表示空闲时间


示例1
输入
1
App1 1 09:00 10:00

09:30
输出
App1
说明
App1注册在9点到10点间，9点半可用的应用名是App1
示例2
输入
2
App1 1 09:00 10:00
App2 2 09:10 09:30
09:20
输出
App2
说明
App1和App2的时段有冲突，App2优先级高，注册App2之后，App1自动注销，因此输出App2.

示例3
输入

2
App1 1 09:00 10:00

App2 2 09:10 09:30

09:50
输出
NA
*/

#include <bits/stdc++.h>
using namespace std;

static int toMin(const string& hhmm) {
    // hhmm: "HH:MM"
    int hh = stoi(hhmm.substr(0, 2));
    int mm = stoi(hhmm.substr(3, 2));
    return hh * 60 + mm;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;
    string dummy;
    getline(cin, dummy); // 吃掉行尾

    // 每分钟占用：appName + priority；空闲用 priority=0
    vector<string> owner(1440, "");
    vector<int> prio(1440, 0);

    int got = 0;
    string line;

    // 读 N 条注册（允许输入中夹杂空行）
    while (got < N && std::getline(cin, line)) {
        // 跳过空行
        bool allSpace = true;
        for (char c : line) if (!isspace((unsigned char)c)) { allSpace = false; break; }
        if (allSpace) continue;

        string app, st, ed;
        int p;
        stringstream ss(line);
        if (!(ss >> app >> p >> st >> ed)) continue; // 输入虽说合法，这里还是防御一下

        int S = toMin(st), E = toMin(ed);
        got++;

        // 起始>=结束：注册不上
        if (S >= E) continue;

        // 若与同优先级冲突：整条注册失败
        bool sameConflict = false;
        for (int t = S; t < E; t++) {
            if (prio[t] == p && !owner[t].empty()) {
                sameConflict = true;
                break;
            }
        }
        if (sameConflict) continue;

        // 否则按优先级逐分钟覆盖
        for (int t = S; t < E; t++) {
            if (prio[t] < p) {
                owner[t] = app;
                prio[t] = p;
            }
            // prio[t] > p：保持原样
            // prio[t] == p：前面已经确保不会发生
        }
    }

    // 读取最后一行查询时间（也可能前面有空行）
    string q;
    while (getline(cin, q)) {
        bool allSpace = true;
        for (char c : q) if (!isspace((unsigned char)c)) { allSpace = false; break; }
        if (!allSpace) break;
    }

    if (q.empty()) return 0;
    // 去掉首尾空格
    {
        int l = 0, r = (int)q.size() - 1;
        while (l <= r && isspace((unsigned char)q[l])) l++;
        while (r >= l && isspace((unsigned char)q[r])) r--;
        q = (l <= r) ? q.substr(l, r - l + 1) : "";
    }

    int T = toMin(q);
    if (T < 0 || T >= 1440 || owner[T].empty()) {
        cout << "NA\n";
    } else {
        cout << owner[T] << "\n";
    }
    return 0;
}
