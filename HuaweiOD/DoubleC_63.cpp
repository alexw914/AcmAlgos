//
// Created by Krisw on 2025/12/26.
//

/*
对于一个连续正整数组成的序列，可以将其拼接成一个字符串，再将字符串里的部分字符打乱顺序。如序列8 9 10 11
12，拼接成的字符串为89101112，
打乱一部分字符后得到90811211，原来的正整数10就被拆成了0和1。现给定一个按如上规则得到的打乱字符的字符串，请将其还原成连续正整数序列，
并输出序列中最小的数字.
输入描述
输入一行，为打乱字符的字符串和正整数序列的长度，两者间用空格分隔，字符审长度不超过200，正整数不超过1000，保证输入可以还原成唯一序列。
输出描述
输出一个数字，为序列中最小的数字
示例1：
输入

19801211 5
输出

8
说明：正常的数字序列为8 9 10 11 12 这5个数字，最小数字为8
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string S;
    int K;
    cin >> S >> K;

    // 创建一个unordered_map，用于统计打乱字符的字符串中各字符的数量
    std::unordered_map<char, int> charCnt;

    for (char c : S) { charCnt[c]++; }

    int i = 1;
    while (i <= 1000 - K + 1) {
        // 创建一个unordered_map，用于计算滑动窗口内各字符的数量
        std::unordered_map<char, int> windowCharCnt;
        for (int j = i; j < i + K; j++) {
            // 将正整数转换为字符串
            std::string num = std::to_string(j);
            // 遍历正整数字符串中的字符
            for (char c : num) { windowCharCnt[c]++; }
        }
        // 初始化一个布尔变量，用于判断滑动窗口内各字符数量是否与打乱字符的字符串中各字符数量一致
        bool isMatch = true;
        // 遍历打乱字符的字符串中的字符
        if (windowCharCnt.size() != charCnt.size()) {
            isMatch = false;
        } // 有可能会出现字符缺了，但是其他字符个数均满足的情况，不确定这种情况是否出现
        else {
            for (const auto& p : charCnt) {
                char c = p.first;
                // 如果滑动窗口内的字符数量与打乱字符的字符串中的字符数量不一致，将isMatch设为false并跳出循环
                if (windowCharCnt[c] != charCnt[c]) {
                    isMatch = false;
                    break;
                }
            }
        }

        // 如果滑动窗口内各字符数量与打乱字符的字符串中各字符数量一致，则输出滑动窗口的起始位置并返回
        if (isMatch) {
            std::cout << i << std::endl;
            return 0;
        }

        // 更新滑动窗口的起始位置
        i++;
    }

    return 0;
}