//
// Created by Krisw on 2026/1/1.
//

/*
给定一个射击比赛成绩单，包含多个选手若干次射击的成绩分数，请对每个选手按其最高3个分数之和进行降序排名，输出降序排名后的选手ID序列。条件如下：

1、一个选手可以有多个射击成绩的分数，且次序不固定。
2、如果一个选手成绩少于3个，则认为选手的所有成绩无效，排名忽略该选手。
3、如果选手的成绩之和相等，则成绩之和相等的选手按照其ID降序排列。

输入描述

输入第一行，一个整数N，表示该场比赛总共进行了N次射击，产生N个成绩分数（2<=N<=100）。
输入第二行，一个长度为N整数序列，表示参与每次射击的选手ID（0<=ID<=99）。
输入第三行，一个长度为N整数序列，表示参与每次射击的选手对应的成绩（0<=成绩<=100）。

输出描述

符合题设条件的降序排名后的选手ID序列。

示例1   输入输出示例仅供调试，后台判题数据一般不包含示例

输入

13
3,3,7,4,4,4,4,7,7,3,5,5,5
53,80,68,24,39,76,66,16,100,55,53,80,55

输出

5,3,7,4

说明

该场射击比赛进行了13次，参赛的选手为{3,4,5,7}。
3号选手成绩：53,80,55，最高3个成绩的和为：80+55+53=188。
4号选手成绩：24,39,76,66，最高3个成绩的和为：76+66+39=181。
5号选手成绩：53,80,55，最高3个成绩的和为：80+55+53=188。
7号选手成绩：68,16,100，最高3个成绩的和为：100+68+16=184。
比较各个选手最高3个成绩的和，有3号=5号>7号>4号，由于3号和5号成绩相等且ID号5>3，所以输出为：5,3,7,4。
*/

#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

vector<int> parseArray(const std::string& line) {
    vector<int> array;
    string item;
    stringstream ss(line);
    while (getline(ss, item, ',')) {
        array.push_back(stoi(item));
    }
    return array;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    cin.ignore();
    string line;
    getline(cin, line);
    auto idArray =parseArray(line);
    getline(cin, line);
    auto scoreArray = parseArray(line);

    std::map<int, priority_queue<int>> scoreMap;
    for (int i = 0; i < N; i++) {
        scoreMap[idArray[i]].push(scoreArray[i]);
    }

    struct Info {
        int id;
        int score_sum = 0;
    };

    vector<Info> infos;
    for (auto& [k, v] : scoreMap) {
        if (v.size() >= 3) {
            Info info;
            info.id = k;
            for (int i = 0; i < 3; i++) {
                info.score_sum += v.top();
                v.pop();
            }
            infos.push_back(info);
        }
    }

    sort(infos.begin(), infos.end(), [](Info& a, Info&b) {
        if (a.score_sum == b.score_sum) return a.id > b.id;
        return a.score_sum > b.score_sum;
    });

    for (int i = 0; i < infos.size(); i++) {
        cout << infos[i].id;
        if (i != infos.size() - 1) cout << ',';
    }
    cout << endl;

    return 0;
}
