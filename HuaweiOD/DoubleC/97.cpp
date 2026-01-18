//
// Created by Krisw on 2026/1/18.
//

/*
商人经营一家店铺，有number 种商品，
由于仓库限制每件商品的最大持有数量是 item[index]

每种商品的价格是 item-price[item_index][day]

通过对商品的买进和卖出获取利润
请给出商人在 days 天内能获取的最大的利润

注:同一件商品可以反复买进和卖出
输入描述
3 第一行输入商品的数量 number

3 第二行输入商品售货天数 days
4 5 6 第三行输入仓库限制每件商品的最大持有数量是item[index]

1 2 3 第一件商品每天的价格

4 3 2 第二件商品每天的价格

1 5 3 第三件商品每天的价格

输出描述：

商人在 days 天内能获取的最大的利润

示例1：

输入：

3

3

4 5 6

1 2 3

4 3 2

1 5 3

输出：

32

示例2：

输入：

1

1

1

1

输出：

0
 */

#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int number;
    cin >> number;

    int days;
    cin >> days;

    vector<long long> cap(number);
    for (int i = 0; i < number; i++) { cin >> cap[i]; }

    long long totalProfit = 0;

    for (int i = 0; i < number; i++) {
        vector<long long> price(days);
        for (int d = 0; d < days; d++) { cin >> price[d]; }

        long long profit = 0;
        for (int d = 1; d < days; d++) {
            if (price[d] > price[d - 1]) {
                profit += (price[d] - price[d - 1]);
            }
        }

        totalProfit += profit * cap[i];
    }

    cout << totalProfit << "\n";
    return 0;
}
