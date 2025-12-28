//
// Created by Krisw on 2025/12/26.
//

/*
题目描述
一座水库在连续多日雨水的冲击下，发生了溃坝事故，解放军赶到现场救灾。其中，水坝两侧坝岩是坚固且高度相等，坝口用宽度为1的柱子的高度图表示、
即一个非负整数数组口-现口数组。例如 [7,3,0,0,7] 其两侧坝岩高度是7、坝口数组则为[3,0,0].坝口面积为(7-4)+(7-0)+(7-0)=18个单位。
解放军手上有一批宽度为1，高度不一的木材，用一个非负整数数组-木材数组表示，例如 [4,7,4,3,3,5] 可作为填补坝口的材料。

解放军在指定溃口和填补木材以及工具约束情况下，使用最优填补策略让溃口面积变为最小，例如[4,7,5]，经填补木材后，原溃口[3,0,0]变为[7,7,5],
溃口面积(7-7)+(7-7)+(7-5)=2个单位，为最小面积，则输出为填补木材的总高度:4+7+5=16.
注意:

1.由于现场工具缺乏，每个宽度为1的溃口只能填补1根木材，每根木材只能整体填补，无法锯断。填补方案优先考虑将溃口填补到最小，
若溃口填补效果一样，即溃口填补效果一样，即溃口面积为最小，则选择耗材最小的方案。
2.溃口:数组长度9 m和木材数组长度n均为>0且<=100,坝岩高度k和木材高度均为>0且<=15;
3.坝口:数组规定第1个高度和最后一个高度是坝岩的高度-描定高度，两者高度相等，绝对不会溃坝、无需填补;
4.溃口:可能会存在多个;
输入描述
输入第一行 为坝口数组长度
第二行为坝口数组
第三行为木材数组长度
第四行为木材数组
输出描述
填补溃口耗费的木材的总高度
示例1
输入

3
8,0,8
2
7,6


输出

7

示例2
输入

5
10,3,0,2,10
6
4,8,6,4,5,6


输出

20

示例3
输入

5
10,3,0,2,10
7
4,13,6,12,5,8,10


输出

30
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

/*
 * 将形如 "10,3,0,2,10" 的字符串解析为整数数组
 */
vector<int> parseArray(const string& line) {
    vector<int> result;
    stringstream ss(line);
    string token;
    while (getline(ss, token, ',')) {
        result.push_back(stoi(token));
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    cin >> m;
    cin.ignore();

    string damLine;
    getline(cin, damLine);
    vector<int> dam = parseArray(damLine);

    int n;
    cin >> n;
    cin.ignore();

    string woodLine;
    getline(cin, woodLine);
    vector<int> woods = parseArray(woodLine);

    // 坝岩高度
    int K = dam.front();

    // 计算溃口深度
    vector<int> depths;
    for (int i = 1; i < m - 1; ++i) {
        int d = K - dam[i];
        if (d > 0) {
            depths.push_back(d);
        }
    }

    // 若无溃口或无木材
    if (depths.empty() || woods.empty()) {
        cout << 0 << '\n';
        return 0;
    }

    // 升序排序
    sort(depths.begin(), depths.end());
    sort(woods.begin(), woods.end());

    long long totalCost = 0;     // 木材总高度消耗
    long long totalGain = 0;     // 填补面积

    int i = 0, j = 0;
    while (i < depths.size() && j < woods.size()) {
        if (woods[j] <= depths[i]) {
            // 木材高度完全用于填补
            totalGain += woods[j];
            totalCost += woods[j];
            ++i;
            ++j;
        } else {
            // 木材过高，溢出部分浪费
            totalGain += depths[i];
            totalCost += woods[j];
            ++i;
            ++j;
        }
    }

    cout << totalCost << '\n';
    return 0;
}
