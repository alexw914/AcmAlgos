//
// Created by Krisw on 2026/1/15.
//

/*
在星球争霸篮球赛对抗赛中，最大的宇宙战队希望每个人都能拿到MVP，MVP的条件是单场最高分得分获得者。
可以并列所以宇宙战队决定在比赛中尽可能让更多队员上场，并且让所有得分的选手得分都相同，
然而比赛过程中的每1分钟的得分都只能由某一个人包揽。输出有得分的队员都是MVP时，最少得MVP得分。

输入描述

输入第一行为一个数字 t ，表示为有得分的分钟数 1 ≤ t ≤ 50
第二行为 t 个数字，代表每一分钟的得分 p， 1 ≤ p ≤ 50

输出描述

输出有得分的队员都是MVP时，最少得MVP得分。

示例1：

输入：

9
5 2 1 5 2 1 5 2 1

输出：

6
说明：

4人MVP，每个人都是6分。
*/

#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    vector<int> p(t, 0);
    for (int i = 0; i < t; i++) {
        cin >> p[i];
    }


    return 0;
}
