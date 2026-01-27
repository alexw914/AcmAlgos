//
// Created by 巫妖王 on 2026/1/19.
//

/*
给定一个非空数组(列表)
起元素数据类型为整型
请按照数组元素十进制最低位从小到大进行排序
十进制最低位相同的元素，相对位置保持不变
当数组元素为负值时，十进制最低为等同于去除符号位后对应十进制值最低位

输入描述
给定一个非空数组(列表)
其元素数据类型为32位有符号整数
数组长度为[1,1000]
输出描述

排序后的数组

示例1：

输入
1,2,5,-21,22,11,55,-101,42,8,7,32
输出
1,-21,11,-101,2,22,42,32,5,55,7,8
*/

#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> parseArray(const string &line, char delim) {
    vector<int> array;
    stringstream ss(line);
    string item;
    while (getline(ss, item, delim)) {
        array.push_back(stoi(item));
    }
    return array;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    getline(cin, line);

    auto a = parseArray(line, ',');

    stable_sort(a.begin(), a.end(), [](int x, int y) {
        return abs(x) % 10 < abs(y) % 10;
    });

    for (int i = 0; i < a.size(); i++) {
        if (i) cout << ",";
        cout << a[i];
    }
    cout << "\n";

    return 0;
}
