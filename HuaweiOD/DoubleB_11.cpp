//
// Created by Krisw on 2025/11/30.
//


/*
题目描述
H国最近在和M国打仗，H国间谍头子Peter负责监视敌国M的兵力部署四情况。M国沿边境线布置了N个营地，Peter的任务就是监视这些营地的兵力部署情况。
中央情报局要研究敌情，所以Peter要汇报一段兵营中哪个连续的K个营地驻兵最少之和是多少，可以作为攻击的突破点，例如:"Peter、
快汇报第2个营地到第10个营地中H连续的3座兵营人数之和最少";而且每个营地的人数在不断变化。请你帮Peter设计一个程序，快速计算汇到的结果
输入描述
第一行3个正整数:N K L
N(N<=50000),表示敌人营地兵营的数量，每个营地编号为1,2,3..N.K表示连续的兵营数,L表示后续要问的命令数量;接下来有N个正整数，
第i个正整数ai四代表第i个营地里开始时有ai个人(1<=ai<=50000)
接下来有行有L条命令。命令有3种形式:
(1) Add i j

i和i为正整数，表示第i个营地增加i个人(i不超过30)

(2)Sub i j

i和j为正整数，表示第i个营地减少j个人(j不超过30)

(3)Query i j

i和j为正整数,i<=j，表示询问问第i个营地到第j个营地，连续H个兵营人数之和最少的总人数其中: j-i+1>=K，每组数据最多有50条命令
输出描述
对于每个Query询问，输出一个整数并回车，表示询问的该段中的连续的K座兵营人数之和最少的数量，这个数保持在int以内。

示例1：

输入：

5 2 3
1 2 2 3 3
Query 1 3
Add 3 6
Query 2 4


输出：

3

10

说明：

说明 第一行第一个正整数5，表示敌人有5个营地，第二个正整数2，表示连续营地 的数量是2，第3个正整数3，表示后续会有3条询问的命令;

接下来一行有 5个正整数，分别表示每个营地里开使的人数，第1个营地开始有1个人，第 2个营地开始有2个人，第3个营地开始有2个人，
第4个营地开始有3个人，第5个营地开始有3个人;

接下来每行有一条命令:第1条命令:Query13表示要查询第1到第3个营地的总人数，结果:1+2=3第一个输出是:3

第2条命令:Add36表示第3个营地增加6个人无需输出
第3条命令:Query24表示查询第2到第4个营地的总人数，结果:2+8=10 第一个输出是:10，注意这里第3个营地人数在第2条命令中增加了6
 */
#include <bits/stdc++.h>
using namespace std;

using LL = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K, L;
    if (!(cin >> N >> K >> L)) return 0;
    vector<LL> camps(N + 1);
    for (int i = 1; i <= N; i++) { cin >> camps[i]; }

    while (L--) {
        string key;
        int i, j;
        cin >> key >> i >> j;
        if (key == "Query") {            // moving window
            LL curSum = 0;
            for (int s = i; s < i + K; ++s) {
                curSum += camps[s];
            }
            LL minSum = curSum;
            for (int s = i + 1; s <= j - K + 1; ++s) {
                curSum = curSum - camps[s - 1] + camps[s + K - 1];
                minSum = min(curSum, minSum);
            }
            cout << minSum << "\n";
        } else if (key == "Add") {
            camps[i] += j;
        } else if (key == "Remove") {
            camps[i] -= j;
        }
    }
    return 0;
}