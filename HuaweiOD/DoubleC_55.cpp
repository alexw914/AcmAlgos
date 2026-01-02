//
// Created by Krisw on 2026/1/1.
//

/*
【分苹果】

A、B两个人把苹果分为两堆，A希望按照他的计算规则等分苹果，他的计算规则是按照二进制加法计算，
并且不计算进位 12+5=9（1100 + 0101 = 9），B的计算规则是十进制加法，包括正常进位，B希望在满足A的情况下获取苹果重量最多。

输入苹果的数量和每个苹果重量，输出满足A的情况下B获取的苹果总重量。

如果无法满足A的要求，输出-1。

数据范围

1 <= 总苹果数量 <= 20000

1 <= 每个苹果重量 <= 10000

输入描述：

输入第一行是苹果数量：3

输入第二行是每个苹果重量：3 5 6

输出描述：

输出第一行是B获取的苹果总重量：11

示例1 输入输出示例仅供调试，后台判题数据一般不包含示例

输入

3
3 5 6

输出

11

示例2 输入输出示例仅供调试，后台判题数据一般不包含示例

输入

8
7258 6579 2602 6716 3050 3564 5396 1773

输出

35165

A的求和方法就是计算异或
令 A 拿最轻的那个苹果（重量为 minVal）
B 拿剩下的所有苹果（总重量为 sum - minVal）
*/

#include<iostream>
#include<vector>
using namespace std;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int num;
    cin >> num;

    vector<int> w;
    while (num--) {
        int weight;
        cin >> weight;
        w.push_back(weight);
    }

    // 因为max_weight < 10000
    int min_weight = 10001;
    int a_weight = 0, b_weight = 0;
    for (auto x : w) {
        a_weight ^= x;
        b_weight += x;
        min_weight = min(min_weight, x);
    }
    // 如果异或结果是0，则有解
    if (a_weight == 0) { cout << b_weight - min_weight << endl; }
    else { cout << -1 << endl; }

    return 0;
}


