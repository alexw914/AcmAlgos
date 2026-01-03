//
// Created by Krisw on 2026/1/3.
//

/*
贫如洗的樵夫阿里巴巴在去砍柴的路上，无意中发现了强盗集团的藏宝地，藏宝地有编号从0~N的箱子，每个箱子上面贴有一个数字。
阿里巴巴念出一个咒语数字，查看宝箱是否存在两个不同箱子，这两个箱子上贴的数字相同，同时这两个箱子的编号之差的绝对值小于等于咒语数字，
如果存在这样的一对宝箱，请返回最先找到的那对宝箱左边箱子的编号，如果不存在则返回-1。
输入描述:
第一行输入一个数字字串，数字之间使用逗号分隔，例如: 1,2,3,1字串中数字个数>=1，<=100000; 每人数字值>=-100000，<=100000:第二行输入咒语数字，例如: 3，咒语数字>=1，<=100000
输出描述:
存在这样的一对宝箱，请返回最先找到的那对宝箱左边箱子的编号，如果不存在则返回-1

示例1
输入:
6,3,1,6
3
输出:

0
示例2
输入:
5, 6, 7, 5, 6, 7
2
输出:

-1
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
using namespace std;

vector<int> parseArray(const string &line) {
    stringstream ss(line);
    string item;
    vector<int> array;
    while (getline(ss, item, ',')) {
        array.push_back(stoi(item));
    }
    return array;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    getline(cin, line);
    auto require = parseArray(line);
    int num;
    cin >> num;

    const int N = require.size();
    unordered_map<int, int> last; // 只需要记录上一次出现的位置，不需要存vector

    for (int i = 0; i < N; ++i) {
        int v = require[i];
        auto it = last.find(v);
        if (it != last.end()) {
            int j = it->second;        // 上一次出现的位置
            if (i - j <= num) {        // 因为 i 递增，i >= j，所以直接 i - j
                cout << j << '\n';
                return 0;
            }
        }
        last[v] = i;
    }

    cout << -1 << '\n';
    return 0;
}