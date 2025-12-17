//
// Created by Krisw on 2025/12/14.
//

/*
题目描述

在系统，网络均正常的情况下组织核酸采样员和志愿者对人群进行 核酸检测筛查。
每名采样员的效率不同，采样效率为N人/小时，

由干外界变化，采样品的效率会以M人1小时为粒度发生变化，M为采样效率浮动粒度，M=N*10%，输入保证N*10%的结果为整数

采样员效率浮动规则:采样员需要一名志愿者协助组织才能发挥正常效率，在此基础上，每增加一名志愿者，效率提升1M，
最多提升3M;如果没有志愿者协助组织，效率下降2M。
怎么安排速度最快?求总最快检测效率(总检查效率为各采样人员效率值相加)。

输入描述

第一行:第一个值，采样品人数，取值范围[1, 100]:第一个值。志愿者人数:取值范围[1, 500]
第二行:各采样员基准效率值(单位人/小时)，取值范围[60，600]，保证序列中每项值计算10%为整数。

输出描述
总最快检测效率(单位人1小时)

示例1：
输入：

2 2

200 200
输出：

400
说明：

输入保证采样员基准效率值序列的每个值*10%为整数。
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int P, V;
    cin >> P >> V;


    vector<int> effi(P);
    for (int i = 0; i < P; i++) cin >> effi[i];

    int base = 0;
    vector<int> gains;
    gains.reserve(4 * P);


    for (auto e : effi) {
        int m = e * 0.1;
        base += e - 2* m;  // 基础效率

        gains.push_back(2 * m);
        gains.push_back(m);
        gains.push_back(m);
        gains.push_back(m);
    }

    // 所有可能增加的效率
    sort(gains.begin(), gains.end(), greater<int>());

    int use = min(V, static_cast<int>(gains.size()));
    long long add = 0;
    for (int i = 0; i < use; i++) add += gains[i];

    cout << (base + add) << "\n";
    return 0;
}
