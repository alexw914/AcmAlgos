//
// Created by Krisw on 2025/12/28.
//

/*
题目描述
考勤记录是分析和考核职工工作时间利用情况的原始依据，也是计算职工工资的原始依据，为了正确地计算职工工资和监督工资基金使用情况，公司决定对员工的手机打卡记录进行异常排查。
如果出现以下两种情况，则认为打卡异常
1.实际设备号与注册设备号不一样
2.或者，同一个员工的两个打卡记录的时间小于60分钟并且打卡距离超过5km。
给定打卡记录的字符串数组clockRecords (每个打卡记录组成为: 工号:时间 (分钟);打距离(km);实际设备号;注册设备号)，返回其中异常的打卡记录(按输入顺序输出)。
输入描述
第一行输入一个数字N，为打卡记录的条数。

后续N行记录分别表示打卡记录：工号:时间 (分钟);打距离(km);实际设备号;注册设备号，以逗号间隔。

输出描述
输出异常的打卡记录，以分号间隔。若无异常打卡记录，则输出字符串null

示例1：
输入

2
100000,10,1,ABCD,ABCD
100000,50,10,ABCD,ABCD
输出

100000,10,1,ABCD,ABCD;100000,50,10,ABCD,ABCD
说明
无

示例2：

输入

2
100000,10,1,ABCD,ABCD
100001,80,10,ABCE,ABCE
输出

null
说明
无异常打卡记录，所以返回null
*/

#include <bits/stdc++.h>
using namespace std;

struct Info {
    int id;
    int time;
    int dist;
    string realDevice;
    string registerDevice;
    string msg;
};

Info parseInfo(const string& line) {
    Info info;
    stringstream ss(line);
    string realDevice, registerDevice, item;
    getline(ss, item, ',');
    info.id = stoi(item);
    getline(ss, item, ',');
    info.time = stoi(item);
    getline(ss, item, ',');
    info.dist = stoi(item);
    getline(ss, item, ',');
    info.realDevice = item;
    getline(ss, item, ',');
    info.registerDevice = item;
    info.msg = line;
    return info;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    cin.ignore();

    string line;
    vector<Info> infos(N);
    vector<int> state(N, 0);
    for (int i =0; i < N; i++) {
        getline(cin,line);
        infos[i] = parseInfo(line);
        if (infos[i].realDevice != infos[i].registerDevice) state[i] = 1;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j || infos[i].id != infos[j].id) continue;
            if (abs(infos[i].time - infos[j].time) < 60 && abs(infos[i].dist - infos[j].dist) > 5 ) {
                state[i] = 1;
                state[j] = 1;
            }
        }
    }

    bool isAllNormal = true;
    for (int i = 0; i < N; i++) {
        if (state[i] == 1) {
            cout << infos[i].msg << ";";
            isAllNormal = false;
        }
    }
    if (isAllNormal) {
        cout << "null" << endl;
    }

    return 0;
}