//
// Created by Krisw on 2025/12/28.
//

/*
题目描述

某网上商场举办优惠活动，发布了满减、打折、无门槛3种 优惠券，分别为:
1：每满100元优惠10元，无使用数限制，如100~199元可以使用1张减10元，200~299可使用2张减20元，以此类推;
2：92折券，1次限使用1张，如100元，则优惠后为92元，
3：无门槛5元优惠券，无使用数限制，直接减5元。

优惠券使用限制：每次最多使用2种优惠券，2种优惠可以叠加(优惠叠加时以优惠后的价格计算)。

以购物200元为例，可以先用92折券优惠到184元，再用1张满减券优惠10元，最终价格是174元，也可以用满减券2张优惠20元为180元，再使用92折券优惠到165(165.6向下取整)，不同使用顺序的优惠价格不同，以最优惠价格为准。在一次购物种，同一类型优惠
券使用多张时必须一次性使用，不能分多次拆开使用(不允许先使用1张满减券，再用打折券，再使用一张满减券)。
请设计实现一种解决方法，帮助购物者以最少的优惠券获得最优的优惠价格。优惠后价格越低越好，同等优惠价格，使用的优惠券越少越好，可以允许某次购物不使用优惠券。

约定：优惠活动每人只能参加一次，每个人的优惠券种类和数量是一样的。

输入描述
1：第一行:每个人拥有的优惠券数量(数量取值范围为[0,10]，按满减、打折、无门槛的顺序输入
2：第二行:表示购物的人数n(1≤n≤10000)
3：最后n行:每一行表示某个人优惠前的购物总价格(价格取值范围(0,1000]，都为整数)。

输出描述
1：每行输出每个人每次购物优惠后的最低价格以及使用的优惠券总数量。每行的输出顺序和输入的顺序保持一致

备注
1.优惠券数量都为整数，取值范围为[0.10]
2.购物人数为整数，取值范围为[1,10000]
3.优惠券的购物总价为整数，取值范围为(0.1000]
4.优惠后价格如果是小数，则向下取整，输出都为整数。

示例1： 输入输出示例仅供调试，后台判题数据一般不包含示例

输入

3 2 5

3
100

200

400
输出

65 6

155 7

338 4
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int cntA, cntB, cntC;
    cin >> cntA >> cntB >> cntC;

    int n;
    cin >> n;
    vector<int> prices(n);
    int maxP = 0;
    for (int i = 0; i < n; ++i) {
        cin >> prices[i];
        maxP = max(maxP, prices[i]);
    }

    // 打折券每次最多用 1 张
    int maxUseB = (cntB > 0 ? 1 : 0);

    // 预处理 1..maxP（也可以直接做到 1000）
    const int MAX_PRICE = max(1000, maxP);
    vector<int> bestPrice(MAX_PRICE + 1, 0);
    vector<int> bestCnt(MAX_PRICE + 1, 0);

    auto applyA = [](int price, int u1) -> int {
        if (u1 == 0) return price;
        if (u1 > price / 100) return -1;        // 不能满足每满100减10的条件
        return price - 10 * u1;
    };

    auto applyB = [](int price, int u2) -> int {
        if (u2 == 0) return price;
        return (price * 92) / 100;
    };

    auto applyC = [](int price, int u3) -> int {
        price -= 5 * u3;
        return price < 0 ? price : 0;
    };

    // 预计算
    for (int P = 1; P <= MAX_PRICE; ++P) {
        int bestP = P;   // 不用券
        int bestC = 0;

        for (int u1 = 0; u1 <= cntA; ++u1) {
            for (int u2 = 0; u2 <= maxUseB; ++u2) {
                if (u2 > cntB) continue;  // 实际上 maxUseB 已保证这一条
                for (int u3 = 0; u3 <= cntC; ++u3) {

                    int typesUsed = (u1 > 0) + (u2 > 0) + (u3 > 0);
                    if (typesUsed == 0) continue;   // 等于不用券，不需要在这里处理
                    if (typesUsed > 2) continue;    // 最多两种券

                    int cnt = u1 + u2 + u3;

                    // 只使用一种类型的券
                    if (typesUsed == 1) {
                        int cur = P;
                        int finalPrice = -1;
                        if (u1 > 0) {
                            finalPrice = applyA(cur, u1);
                        } else if (u2 > 0) {
                            finalPrice = applyB(cur, u2);
                        } else { // u3 > 0
                            finalPrice = applyC(cur, u3);
                        }
                        if (finalPrice < 0) continue;  // 无法使用（主要是 A 券条件不满足）

                        if (finalPrice < bestP ||
                            (finalPrice == bestP && cnt < bestC)) {
                            bestP = finalPrice;
                            bestC = cnt;
                        }
                    }
                    // 使用两种不同类型的券，需要考虑顺序
                    else { // typesUsed == 2
                        // 顺序 1: typeX -> typeY
                        auto calc_with_order = [&](int firstType, int secondType) {
                            int cur = P;
                            // first
                            if (firstType == 1) {
                                cur = applyA(cur, u1);
                            } else if (firstType == 2) {
                                cur = applyB(cur, u2);
                            } else { // 3
                                cur = applyC(cur, u3);
                            }
                            if (cur < 0) return;  // 不合法

                            // second
                            if (secondType == 1) {
                                cur = applyA(cur, u1);
                            } else if (secondType == 2) {
                                cur = applyB(cur, u2);
                            } else { // 3
                                cur = applyC(cur, u3);
                            }
                            if (cur < 0) return;  // 不合法

                            int finalPrice = cur;
                            if (finalPrice < bestP ||
                                (finalPrice == bestP && cnt < bestC)) {
                                bestP = finalPrice;
                                bestC = cnt;
                            }
                        };

                        // 判定是哪两种券
                        if (u1 > 0 && u2 > 0) {
                            calc_with_order(1, 2);
                            calc_with_order(2, 1);
                        } else if (u1 > 0 && u3 > 0) {
                            calc_with_order(1, 3);
                            calc_with_order(3, 1);
                        } else if (u2 > 0 && u3 > 0) {
                            calc_with_order(2, 3);
                            calc_with_order(3, 2);
                        }
                    }
                }
            }
        }

        bestPrice[P] = bestP;
        bestCnt[P] = bestC;
    }

    // 输出每个人的结果
    for (int i = 0; i < n; ++i) {
        int P = prices[i];
        cout << bestPrice[P] << " " << bestCnt[P] << "\n";
    }

    return 0;
}


