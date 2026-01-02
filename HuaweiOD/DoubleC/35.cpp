//
// Created by Krisw on 2025/12/21.
//

/*
为了提升软件编码能力，小王制定了刷题计划，他选了题库中的n道题，编号从0到n-1，并计划在m天内按照题目编号顺序刷完所有的题目 (注意，小王不能用多天完成同一题)
在小王刷题计划中，小王需要用time[i]的时间完成编号i的题目此外，小王还可以查看答案，可以省去该题的做题时间。
为了真正达到刷题效果，小王每天最多直接看一次答案。我们定义m天中做题时间最多的一天耗时为T (直接看答案的题目不计入做题总时间)。
请你帮小王求出最小的T是多少
输入描述
第一行输入为 time，time[i]的时间完成编号i的题目

第二行输入为m，m表示几天内完成所有题目，1 <= m <= 180
输出描述
最小耗时整数T


示例1：

输入
999,999,999

4
输出

0
说明

在前三天中，小王每天都直接看答案，这样他可以在三天内完成所有的题目并不花任何时间

示例2：
输入
1,2,2,3,5,4,6,7,8
5
输出

4
说明
第一天完成前3题，第3题看答案第二天完成第4题和第5题，第5题看答案:第三天完成第6和第7题，第7提看答案:第四天完成第8题，直接看答案:第五天完成第9题，直接看答案
*/

#include <bits/stdc++.h>
using namespace std;

static vector<long long> parseTimes(const string& s) {
    vector<long long> a;
    long long num = 0;
    bool inNum = false;
    for (char c : s) {
        if (isdigit((unsigned char)c)) {
            num = num * 10 + (c - '0');
            inNum = true;
        } else {
            if (inNum) {
                a.push_back(num);
                num = 0;
                inNum = false;
            }
        }
    }
    if (inNum) a.push_back(num);
    return a;
}

static bool feasible(const vector<long long>& t, int m, long long T) {
    int days = 1;
    long long sum = 0, mx = 0;

    for (long long x : t) {
        long long nsum = sum + x;
        long long nmx  = max(mx, x);

        if (nsum - nmx <= T) {
            sum = nsum;
            mx = nmx;
        } else {
            // 开新的一天
            days++;
            sum = x;
            mx = x;

            // 单题一天的最小耗时 = x - x = 0，一定 <= T (只要 T>=0)
            // 所以这里一般不会失败，但保留健壮性：
            if (sum - mx > T) return false;

            if (days > m) return false; // 提前剪枝
        }
    }
    return days <= m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line1;
    if (!getline(cin, line1)) return 0;
    vector<long long> time = parseTimes(line1);

    string line2;
    while (getline(cin, line2)) {
        if (!line2.empty()) break;
    }
    int m = stoi(line2);

    int n = (int)time.size();
    if (n == 0) { // 题目一般不会给空，但防一下
        cout << 0;
        return 0;
    }

    // 若 m >= n，每天最多做1题，并且都可以看答案 => 每天耗时0 => T=0
    if (m >= n) {
        cout << 0;
        return 0;
    }

    long long lo = 0, hi = 0;
    for (auto x : time) hi += x;  // 上界：全放一天且不看答案也不会超过 sum

    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (feasible(time, m, mid)) hi = mid;
        else lo = mid + 1;
    }

    cout << lo;
    return 0;
}

