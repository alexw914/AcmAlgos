//
// Created by Krisw on 2025/12/12.
//

/*
运维工程师采集到某产品线网运行一天产生的日志n条

现需根据日志时间先后顺序对日志进行排序

日志时间格式为H:M:S.N

H表示小时(0~23)

M表示分钟(0~59)

S表示秒(0~59)

N表示毫秒(0~999)

时间可能并没有补全

也就是说

01:01:01.001也可能表示为1:1:1.1

输入描述

第一行输入一个整数n表示日志条数，1<=n<=100000
接下来n行输入n个时间
输出描述

按时间升序排序之后的时间
如果有两个时间表示的时间相同
则保持输入顺序
示例1   输入输出示例仅供调试，后台判题数据一般不包含示例

输入

2
01:41:8.9
1:1:09.211

输出

1:1:09.211
01:41:8.9

示例2   输入输出示例仅供调试，后台判题数据一般不包含示例

输入

3
23:41:08.023
1:1:09.211
08:01:22.0

输出

1:1:09.211
08:01:22.0
23:41:08.023

示例3   输入输出示例仅供调试，后台判题数据一般不包含示例

输入

2
22:41:08.023
22:41:08.23

输出

22:41:08.023
22:41:08.23

注：时间相同保持输入顺序
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    struct TimeInfo {
        std::string timeStr;
        int hour;
        int minute;
        int second;
        int milliseconds;
    };

    std::vector<TimeInfo> times;
    while (n--) {
        string line;
        getline(cin, line);
        if (line.empty()) {
            n++;
            continue;
        }
        TimeInfo info;
        info.timeStr = line;
        string tmp;
        stringstream ss(line);
        getline(ss, tmp, ':');
        info.hour = stoi(tmp);
        getline(ss, tmp, ':');
        info.minute = stoi(tmp);
        getline(ss, tmp, '.');
        info.second = stoi(tmp);
        getline(ss, tmp);
        info.milliseconds = stoi(tmp);
        times.push_back(info);
    }

    sort(times.begin(), times.end(), [](TimeInfo &a, TimeInfo &b) {
        if (a.hour != b.hour) return a.hour < b.hour;
        if (a.minute != b.minute) return a.minute < b.minute;
        if (a.second != b.second) return a.second < b.second;
        return a.milliseconds <
            b.milliseconds;
    });

    for (auto &time: times) {
        cout << time.timeStr << endl;
    }
    return 0;
}
