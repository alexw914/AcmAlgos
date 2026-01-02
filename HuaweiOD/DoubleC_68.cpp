//
// Created by Krisw on 2026/1/2.
//

/*
题目描述
某公司有一笔资金(m万元)计划进行投资，前期调研分析了多种(n种)产品，分析得出了每种产品的预期收益率(e%)和风险等级(记为r,用1~10表示。数值越大表示风险越高)，
公司风控部门要求投资产品的风险等级不能超过x且单个产品的投资金额不能超过y元，请规划一个满足公司风控要求的最大预期收益的投资方案并输出改方案的预期收益。


输入描述
输入的第一行为可用于投资的金额m(万元)，调研的投资产品种类数n(种)，风险部门要求的最高可以投资风险等级x。单个产品的最大投资金额y(万元)，用空格分割;
第二行开始为每个产品的预期收益率e(%)和每个产品的风险等级r，用空格分割。
不考虑非法输入，所有输入都是正整数，输出结果四舍五入取整，输入输出口均小于2^31

输出描述
输出计算的最大预期收益
示例1：

输入：

100 7 5 10
10 3
15 5
14 3
20 7
18 6
17 4
30 9

输出：
6
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    int m, n, x, y;
    cin >> m >> n >> x >> y;
    struct Info {
        int e; // 收益率 %
        int r; // 风险等级
    };
    vector<Info> infos;
    infos.reserve(n);
    for (int i = 0; i < n; i++) {
        int e, r;
        cin >> e >> r;
        if (r <= x) {
            infos.push_back({e, r}); // 只保留风险合规的产品
        }
    }
    if (infos.empty() || m <= 0) {
        cout << 0 << "\n";
        return 0;
    }

    // 按收益率从高到低排序
    sort(infos.begin(), infos.end(), [](const Info &a, const Info &b) {
        return a.e > b.e;
    });

    int remaining = m;  // 剩余资金
    double profit = 0.0; // 总收益，用长浮点防止精度问题

    for (const auto &p : infos) {
        if (remaining <= 0) break;
        int invest = min(remaining, y);
        profit += invest * p.e / 100.0L;
        remaining -= invest;
    }

    // 四舍五入取整
    int ans = round(profit);
    cout << ans << "\n";

    return 0;
}
