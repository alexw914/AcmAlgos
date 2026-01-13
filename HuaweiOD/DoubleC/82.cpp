//
// Created by Krisw on 2026/1/12.
//

/*
题目描述:
记账本上记录了若干条多国货币金额，需要转换成人民币分 (fen)，汇总后输出每行记录一条金额，金额带有货币单位，格式为数字+单位，
可能是单独元，或者单独分，或者元与分的组合要求将这些货币全部换算成人民币分 (fen) 后进行汇总，
汇总结果仅保留整数，小数部分舍弃。元和分的换算关系都是1:100，如下:
1CNY=100fen (1元=100分)
1HKD=100cents (1港元=100港分)1JPY=100sen (1日元=100仙)
1EUR=100eurocents (1欧元=100欧分)
1GBP=100pence (1英镑=100便士)
汇率如下表

CNY	JPY	HKD	EUR	GBP
100	1825	123	14	12
即100CNY=1825JPY=123HKD=14EUR=12GBP

输入描述:
第一行输入为N，N表示记录数。0<N<100之后N行，每行表示一条货币记录，且该行只会是一种货币。

输出描述:
将每行货币转换成人民币分 (fen) 后汇总求和，只保留整数部分输出格式只有整数数字，不带小数，不带单位
补充说明:
输出格式只有数字，不带单位

示例1
输入:

1
100CNY
输出:
10000
说明:
100CNY转换后是10000fen，所以输出结果为10000
示例2
输入:

1
3000fen
输出:
3000
说明:
3000fen，结果就是3000

示例3
输入:

1
123HKD
输出:
10000
说明:
HKD与CNY的汇率关系是123:100，所以换算后，输出结果为10000
示例4
输入:
2
20CNY53fen
53HKD87cents
输出:
6432
说明:
20元53分+53港元87港分，换算成人民币分后汇总，为6432
*/

#include <iostream>
using namespace std;

long long toFen(long long val, const string& unit) {
    if (unit == "fen") return val;

    // 先统一转为 CNY，再转 fen
    double cny = 0.0;
    if (unit == "CNY") cny = val;
    else if (unit == "JPY") cny = val * 100.0 / 1825.0;
    else if (unit == "HKD") cny = val * 100.0 / 123.0;
    else if (unit == "EUR") cny = val * 100.0 / 14.0;
    else if (unit == "GBP") cny = val * 100.0 / 12.0;
    else if (unit == "cents") cny = val * 100.0 / 123.0 / 100.0;      // HKD cents
    else if (unit == "sen")   cny = val * 100.0 / 1825.0 / 100.0;     // JPY sen
    else if (unit == "pence") cny = val * 100.0 / 12.0 / 100.0;       // GBP pence
    else if (unit == "eurocents") cny = val * 100.0 / 14.0 / 100.0;   // EUR cents

    return (long long)(cny * 100.0); // 转 fen 并向下取整
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    long long totalFen = 0;

    while (N--) {
        string s;
        cin >> s;

        int i = 0;
        while (i < s.size()) {
            long long num = 0;
            while (i < s.size() && isdigit(s[i])) {
                num = num * 10 + (s[i] - '0');
                i++;
            }

            string unit;
            while (i < s.size() && isalpha(s[i])) {
                unit.push_back(s[i]);
                i++;
            }

            totalFen += toFen(num, unit);
        }
    }

    cout << totalFen << "\n";
    return 0;
}
