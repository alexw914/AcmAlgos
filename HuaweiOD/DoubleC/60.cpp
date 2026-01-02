//
// Created by Krisw on 2026/1/2.
//

/*
停车场统计当日总收费，包月的车不统计，不包月的车半个小时收一块钱，不满半小时不收钱，如果超过半小时，零头不满半小时按半小时算，
每天11:30-13:30时间段不收钱， 如果一辆车停车时间超过8小时后不收费。现提供停车场进出车辆的统计信息，需要你来计算停车场统计当日的总收费。


输入描述
第一行输入一个整数n 表示今日进出停车场的包月的车辆数

下一个行输入包月车的车牌号，以空格分割

接下来每一行输出进出停车场的车辆信息。

进入停车场格式为(时间 车牌号 enter)

离开停车场格式为(时间 车牌号 leave)
输出描述
输出今日总收费

示例1：

输入：

2
AAA CCC
8:00 AAA enter
10:00 AAA leave
输出：

0

示例2：

输入：

2
AAA CCC
8:00 AAA enter
10:00 AAA leave
8:00 BBB enter
9:00 BBB leave
输出：

2
*/

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

int toMinute(const string &s) {
    // s: "HH:MM"
    int h = stoi(s.substr(0, 2));
    int m = stoi(s.substr(3, 2));
    return h * 60 + m;
}

int overlap(int l1, int r1, int l2, int r2) {
    int l = max(l1, l2);
    int r = min(r1, r2);
    return max(0, r - l);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // 读取包月车
    unordered_set<string> monthly;
    monthly.reserve(n * 2);

    for (int i = 0; i < n; ++i) {
        string plate;
        cin >> plate;
        monthly.insert(plate);
    }
    cin.ignore();

    // 午休免费时段
    const int freeStart = 11 * 60 + 30; // 11:30
    const int freeEnd = 13 * 60 + 30; // 13:30

    // 当前在场车辆的进入时间
    unordered_map<string, int> inTime;
    // 每辆非包月车当天累计计费分钟数（未封顶）
    unordered_map<string, int> totalMinutes;

    string line;
    while (getline(cin, line)) {
        if (line.empty()) break;
        stringstream ss(line);
        string timeStr, plate, action;
        getline(ss, timeStr, ' ');
        getline(ss, plate, ' ');
        getline(ss, action, ' ');

        if (monthly.count(plate)) { continue; }

        int t = toMinute(timeStr);

        if (action == "enter") {
            inTime[plate] = t;
        } else if (action == "leave") {
            auto it = inTime.find(plate);
            if (it == inTime.end()) { continue; }

            int t_in = it->second;
            int t_out = t;
            if (t_out < t_in) {
                inTime.erase(it);
                continue;
            }

            int dur = t_out - t_in;
            // 与免费午休时间的重叠
            int freeDur = overlap(t_in, t_out, freeStart, freeEnd);
            int chargeDur = max(0, dur - freeDur);

            totalMinutes[plate] += chargeDur;

            inTime.erase(it);
        }
    }

    long long totalFee = 0;
    const int maxMinutes = 8 * 60; // 8小时封顶

    for (auto &kv: totalMinutes) {
        int mins = kv.second;
        if (mins <= 0) continue;

        // 超过8小时只收8小时的钱
        if (mins > maxMinutes) mins = maxMinutes;

        // 每半小时1块，不满半小时向上取整
        int fee = (mins + 29) / 30;
        totalFee += fee;
    }

    cout << totalFee << "\n";

    return 0;
}
