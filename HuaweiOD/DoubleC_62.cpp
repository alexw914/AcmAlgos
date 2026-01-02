//
// Created by Krisw on 2026/1/2.
//

/*
题目描述:
去除文本多余空格，但不去除配对单引号之间的多余空格。给出关键词的起始和结束下标，去除多余空格后刷新关键词的起始和结束下标。
输入描述:
输入为两行字符串:
第一行: 待去除多余空格的文本，用例保证如果有单引号，则单引号成对出现，且单引号可能有多对.第二行: 关键词的开始和结束坐标，关键词间以逗号区分，关键词内的开始和结束位置以单空格区分
例如:
Life is painting a picture, not doing 'a sum'
8 15,20 26,43 45
关键单词为: painting picture sum
输出描述:
输出为两行字符串:
第一行: 去除多余空格后的文本
第二行: 去除多余空格后的关键词的坐标开始和结束位置，为数组方式输出
例如:
Life is painting a  picture, not doing 'a sum'

[8,15][19, 25][42, 44]

条件约束:
1，不考虑关键词起始和结束位置为空格的场景
2，单词的的开始和结束下标保证涵盖一个完整的单词，即一个坐标对开始和结束下标之间不会有多余的空格:
3，如果有单引号，则用例保证单引号成对出现:
4，关键词可能会重复:
5，文本字符长度length取值范围: [0,100000]:

示例1
输入
Life is painting a  picture, not doing 'a sum'  (a和picture之间有两个英文空格)

8 15,20 26,43 45
输出:
Life is painting a picture, not doing 'a sum'

[8,15][19,25][42, 44]
说明:
a和picture中间多余的空格进行删除

示例2
输入:
Life is painting a picture, not doing 'a sum'

8 15,19 25,42 44
输出
Life is painting a picture, not doing 'a sum'

[8,15][19, 25][42, 44]
说明:
a和sum之间有多余的空格，但是因为有成对单引号，不去除多余空格
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s, coordLine;
    getline(cin, s);
    getline(cin, coordLine);

    // 1. 解析关键词区间
    vector<pair<int,int>> ranges;
    if (!coordLine.empty()) {
        stringstream ss(coordLine);
        string part;
        // 按逗号分块
        while (getline(ss, part, ',')) {
            if (part.empty()) continue;
            stringstream ss2(part);
            int l, r;
            if (ss2 >> l >> r) {
                ranges.emplace_back(l, r);
            }
        }
    }

    int n = static_cast<int>(s.size());
    vector<int> newIndex(n, -1);
    string t;
    t.reserve(n);

    bool inQuote = false;
    bool lastSpace = false;  // 引号外，最后写入是否是空格

    // 2. 构造新文本 + 下标映射
    for (int i = 0; i < n; ++i) {
        char c = s[i];
        if (c == '\'') {
            // 单引号：始终保留
            newIndex[i] = (int)t.size();
            t.push_back(c);
            inQuote = !inQuote;
            lastSpace = false;  // 不是空格
        } else if (c == ' ') {
            if (inQuote) {
                // 引号内：完全保留空格
                newIndex[i] = (int)t.size();
                t.push_back(c);
                // 不影响引号外的 lastSpace
            } else {
                // 引号外：压缩空格
                if (!lastSpace) {
                    newIndex[i] = (int)t.size();
                    t.push_back(c);
                    lastSpace = true;
                } else {
                    // 多余空格：丢弃
                }
            }
        } else {
            // 普通字符：始终保留
            newIndex[i] = (int)t.size();
            t.push_back(c);
            if (!inQuote) {
                lastSpace = false;
            }
        }
    }

    // 3. 刷新关键词坐标
    vector<pair<int,int>> newRanges;
    newRanges.reserve(ranges.size());
    for (auto &p : ranges) {
        int l = p.first;
        int r = p.second;
        int nl = newIndex[l];
        int nr = newIndex[r];
        newRanges.emplace_back(nl, nr);
    }

    // 4. 输出
    cout << t << "\n";
    for (size_t i = 0; i < newRanges.size(); ++i) {
        cout << "[" << newRanges[i].first << "," << newRanges[i].second << "]";
    }
    cout << "\n";

    return 0;
}

