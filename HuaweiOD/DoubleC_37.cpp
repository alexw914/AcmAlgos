//
// Created by Krisw on 2025/12/22.
//

/*
斗地主起源于湖北十堰房县，据说是一位叫吴修全的年轻人根据当地流行的扑克玩法“跑得快”改编的，如今已风靡整个中国，并流行于互联网上。
牌型：
单顺，又称顺子，最少5张牌，最多12张牌(3…A)不能有2，也不能有大小王，不计花色。
例如：
3-4-5-6-7-8，7-8-9-10-J-Q，3-4-5-6-7-8-9-10-J-Q-K-A
可用的牌 3<4<5<6<7<8<9<10<J<Q<K<A<2<B(小王)<C(大王)，每种牌除大小王外有四种花色
(共有13×4+2张牌)

输入描述
输入的第一行为当前手中的牌
输入的第二行为已经出过的牌(包括对手出的和自己出的牌)

输出描述
最长的顺子
对手可能构成的最长的顺子(如果有相同长度的顺子，输出牌面最大的那一个)，
如果无法构成顺子，则输出 NO-CHAIN。

示例
示例1
输入
3-3-3-4-4-5-5-6-7-8-9-10-J-Q-K-A-A-A-A
4-5-6-7-8-8-8
输出
9-10-J-Q-K

示例2
输入
3-3-3-3-8-8-8-8
K-K-K-K
输出
NO-CHAIN
说明
剩余的牌无法构成顺子
*/

#include <bits/stdc++.h>
using namespace std;

static vector<string> split_dash(const string &s) {
    vector<string> out;
    if (s.empty()) return out;
    string cur;
    for (char c : s) {
        if (c == '-') {
            out.push_back(cur);
            cur.clear();
        } else {
            cur.push_back(c);
        }
    }
    out.push_back(cur);
    return out;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string handLine, playedLine;
    if (!getline(cin, handLine)) handLine = "";
    if (!getline(cin, playedLine)) playedLine = "";

    // 映射：3..10, J,Q,K,A,2,B(小王),C(大王)
    unordered_map<string,int> toVal;
    for (int i = 3; i <= 10; i++) toVal[to_string(i)] = i;
    toVal["J"] = 11; toVal["Q"] = 12; toVal["K"] = 13; toVal["A"] = 14;
    toVal["2"] = 15; toVal["B"] = 16; toVal["C"] = 17;

    vector<string> toFace(18);
    for (auto &kv : toVal) toFace[kv.second] = kv.first;

    // 整副牌计数
    vector<int> cnt(18, 0);
    for (int v = 3; v <= 15; v++) cnt[v] = 4; // 3..2 每种4张
    cnt[16] = 1; // 小王
    cnt[17] = 1; // 大王

    // 扣掉你的手牌
    for (auto &card : split_dash(handLine)) {
        auto it = toVal.find(card);
        if (it != toVal.end()) cnt[it->second]--;
    }
    // 扣掉已出牌
    for (auto &card : split_dash(playedLine)) {
        auto it = toVal.find(card);
        if (it != toVal.end()) cnt[it->second]--;
    }

    // 找 3..A(14) 的最长连续段（每点剩>=1即可）
    int bestLen = 0, bestStart = -1, bestEnd = -1;

    int curStart = -1, curLen = 0;
    for (int v = 3; v <= 14; v++) {
        if (cnt[v] >= 1) {
            if (curStart == -1) {
                curStart = v;
                curLen = 1;
            } else {
                curLen++;
            }
        } else {
            if (curStart != -1) {
                int curEnd = v - 1;
                if (curLen >= 5) {
                    if (curLen > bestLen || (curLen == bestLen && curEnd > bestEnd)) {
                        bestLen = curLen;
                        bestStart = curStart;
                        bestEnd = curEnd;
                    }
                }
                curStart = -1;
                curLen = 0;
            }
        }
    }
    // 收尾
    if (curStart != -1) {
        int curEnd = 14;
        if (curLen >= 5) {
            if (curLen > bestLen || (curLen == bestLen && curEnd > bestEnd)) {
                bestLen = curLen;
                bestStart = curStart;
                bestEnd = curEnd;
            }
        }
    }

    if (bestLen == 0) {
        cout << "NO-CHAIN\n";
    } else {
        for (int v = bestStart; v <= bestEnd; v++) {
            if (v != bestStart) cout << "-";
            cout << toFace[v];
        }
        cout << "\n";
    }

    return 0;
}

