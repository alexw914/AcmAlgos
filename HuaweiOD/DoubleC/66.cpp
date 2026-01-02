//
// Created by Krisw on 2026/1/2.
//

/*
误码率是最常用的数据通信传输质量指标。它可以理解为“在多少位数据中出现一位差错”。移动通信 网络中的误码率主要是指比特误码率，
其计算公式如下:比特误码率=错误比特数/传输总比特数。为了简单，我们使用字符串来标识通信的信息，一个字符错误了，
就认为出现了一个误码输入一个标准的字符串，和一个传输后的字符串，计算误码率字符串会被压缩。
例:“2A3B4D5X1Z”表示"AABBBDDDDXXXXXZ"

用例会保证两个输入字符串解压后长度一致，解压前的长度不一定一致每个生成后的字符串长度<100000000.
输入描述
两行，分别为两种字符串的压缩形式。
每行字符串(压缩后的) 长度<100000
输出描述
一行，错误的字数量/展开后的总长度
备注
注意: 展开后的字符串不含数字

示例1：
输入

3A3B
2A4B
输出

1/6
示例2：
输入
5Y5Z
5Y5Z

输出
0/10
示例3：
输入
4Y5Z
9Y

输出
5/9
*/

#include <iostream>
#include <vector>
using namespace std;

vector<pair<long long, char> > parseRuns(const string &s) {
    vector<pair<long long, char> > runs;
    int n = (int) s.size();
    int i = 0;

    while (i < n) {
        long long cnt = 0;
        // 解析数字部分（可能是多位数）
        while (i < n && isdigit((unsigned char) s[i])) {
            cnt = cnt * 10 + (s[i] - '0');
            ++i;
        }
        // 接下来应该是一个字符（题目保证展开结果不包含数字）
        if (i >= n) break; // 防御性处理，也可以直接认为输入总是合法
        char c = s[i];
        ++i;
        runs.push_back({cnt, c});
    }

    return runs;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    getline(cin, line);
    auto r1 = parseRuns(line);
    getline(cin, line);
    auto r2 = parseRuns(line);

    size_t i1 = 0, i2 = 0;
    long long rem1 = 0, rem2 = 0;
    char c1 = 0, c2 = 0;

    long long total = 0; // 展开后的总长度
    long long err = 0; // 错误的字符数

    while (i1 < r1.size() || rem1 > 0 || i2 < r2.size() || rem2 > 0) {
        if (rem1 == 0) {
            c1 = r1[i1].second;
            rem1 = r1[i1].first;
            ++i1;
        }
        if (rem2 == 0) {
            c2 = r2[i2].second;
            rem2 = r2[i2].first;
            ++i2;
        }

        long long use = min(rem1, rem2); // 本轮对齐长度

        if (c1 != c2) {
            err += use;
        }
        total += use;
        rem1 -= use;
        rem2 -= use;
    }

    cout << err << "/" << total << "\n";
    return 0;
}
