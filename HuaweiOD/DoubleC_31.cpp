//
// Created by Krisw on 2025/12/21.
//
/*
某设备需要记录每分钟检测到的指标值。为了节约存储口空间，将连续相同指标值的记录合并，
压缩之前:202411231000,11 202411231001,11 202411231002,12 202411231003,12 202411231004,10 202411231005,17 202411231006,17 202411231007,17
压缩之后:202411231000,202411231001,11
        202411231002,202411231003,12
        202411231004,202411231004,10
        202411231005,202411231007,17


查询时，根据输入的时间范围进行查询，需要返回回时间范围内记录的每分钟的指标值，如果某个时间点没有记录值，则此条记录忽略不返回。


输入描述
第一行为查询的时间范围，格式是:startTime.endTime。查询的时间范围为闭区间，即大于等于statTime且小于等于endTimestartTime<=endTime，
且他们跨度的分钟数小于100;
第二行为压缩 日志记录只的行数，100>=N>0;
第三行及以后为压缩日志内容。每一行的格式为:startTime,endTime,kpi，其中 startTime<=endTime，10^5>kpi>=0;记录已按升序进行排序。
不保证两行记录之间是紧密连接、startTime和endTime的时间跨度可能很大。如:上一行的数据显示范围是202411231540 202411231542，
下一行的数据显示可以是 202411231544,202411231547，中间202411231543的数据可能由于其他原因缺失。
输出描述
输出描述 查询到的日志清单，如:202411231010,11 202411231011,10 202411231012,10 202411231013,16
输出结果按数据时间升序排序。
补充说明 输入的数据可能超出当前已存储的数据范围，此时只输出查询到的数据。如果从头到尾都没有查询到记录，则输出-1。

示例1：

输入：

202411231010,202411231013
4
202411231000,202411231010,11
202411231011,202411231012,10
202411231013,202411231020,16
202411231021,202411231028,17


输出：

202411231010,11
202411231011,10
202411231012,10
202411231013,16


说明：

202411231010时间的指标值在202411231000,202411231010范围内，
值是11 202411231011,202411231012时间的指标值在202411231011,202411231012范围内，
值是10 202411231013时间的指标值在202411231013,202411231020范围内，值是16
*/

#include <bits/stdc++.h>
using namespace std;

// 把 "yyyyMMddHHmm" 转成 time_t（按 UTC 处理，避免夏令时问题）
static time_t parseTimeUTC(const string& s) {
    std::tm tm{};
    tm.tm_year = stoi(s.substr(0, 4)) - 1900;
    tm.tm_mon  = stoi(s.substr(4, 2)) - 1;
    tm.tm_mday = stoi(s.substr(6, 2));
    tm.tm_hour = stoi(s.substr(8, 2));
    tm.tm_min  = stoi(s.substr(10, 2));
    tm.tm_sec  = 0;

#if defined(_WIN32)
    // Windows 没有 timegm，这里给出一个保守替代：使用 mktime（可能受本地时区影响）
    // 若你的 OJ 是 Linux，一般会走下面的 timegm 分支
    return mktime(&tm);
#else
    return timegm(&tm);
#endif
}

// time_t 转回 "yyyyMMddHHmm"（UTC）
static string formatTimeUTC(time_t t) {
    std::tm* ptm = gmtime(&t);
    char buf[32];
    // yyyyMMddHHmm
    strftime(buf, sizeof(buf), "%Y%m%d%H%M", ptm);
    return string(buf);
}

struct Seg {
    time_t st, ed;
    int kpi;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    if (!getline(cin, line)) return 0;

    string qStartStr, qEndStr;
    {
        stringstream ss(line);
        getline(ss, qStartStr, ',');
        getline(ss, qEndStr);
    }

    int N;
    cin >> N;
    getline(cin, line); // 吃掉 N 后面的换行

    vector<Seg> segs;
    segs.reserve(N);

    for (int readCnt = 0; readCnt < N; ) {
        if (!getline(cin, line)) break;
        if (line.empty()) continue; // 跳过空行，不计数
        string stStr, edStr, kpiStr;
        stringstream ss(line);
        getline(ss, stStr, ',');
        getline(ss, edStr, ',');
        getline(ss, kpiStr);

        Seg s;
        s.st = parseTimeUTC(stStr);
        s.ed = parseTimeUTC(edStr);
        s.kpi = stoi(kpiStr);
        segs.push_back(s);

        readCnt++;
    }

    time_t qStart = parseTimeUTC(qStartStr);
    time_t qEnd   = parseTimeUTC(qEndStr);

    // 线性扫描：segs 已按时间升序
    size_t idx = 0;
    bool any = false;

    for (time_t cur = qStart; cur <= qEnd; cur += 60) { // 每次+1分钟
        while (idx < segs.size() && segs[idx].ed < cur) idx++;
        if (idx >= segs.size()) break;

        if (segs[idx].st <= cur && cur <= segs[idx].ed) {
            cout << formatTimeUTC(cur) << "," << segs[idx].kpi << "\n";
            any = true;
        }
        // else：cur 落在缺失区间，忽略不输出
    }

    if (!any) cout << -1 << "\n";
    return 0;
}

