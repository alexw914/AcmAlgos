//
// Created by Krisw on 2026/1/3.
//

/*
一个跳数jump，及幸存数量 left。给一个正整数数列 nums，运算过程为:从索引0的位置开始向后跳，中间跳过了J个数字，
命中索引为 J+1 的数字，该数被敲出，并从该点起跳，以此类推，直到幸存 left 个数为止，然后返回幸存数之和。
约束:
1:0是第一个起跳点
2:起跳点和命中点之间间隔 iump 个数字，已被敲出的数字不计入在内，
3:跳到未尾时无缝从头开始 (循环查找) ，并可以多次循环
4:若起始时 left > len(nums) 则无需跳数处理过程
方法设计:
* @param nums 正整数数列，长度范围 [1，10000
* @param jump 跳数，范围 [1，10000]
* @param left 幸存数量，范围 [0，10000]
* @return 幸存数之和
int sumOfLeft(int[] nums, int iump, int left){
}

输入描述
第一行输入正整数数列
第二行输入跳数
第三行输入幸存数量
输出描述
输出幸存数之和
示例1：

输入
1,2,3,4,5,6,7,8,9
4
3
输出

13

说明
从1 (索引为0)开始起跳，中间跳过 4 个数字，因此依次删除 6,2,8,5,4,7。剩余1,3,9，返回和为13
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <list>
using namespace std;
using LL = long long;

vector<int> parseArray(const string &line) {
    stringstream ss(line);
    string item;
    vector<int> array;
    while (getline(ss, item, ',')) {
        array.push_back(stoi(item));
    }
    return array;
}

LL sumOfLeft(const vector<int> &nums, int jump, int left) {
    int n = static_cast<int>(nums.size());
    if (left <= 0) return 0;             // 需要幸存 0 个
    if (left >= n) {                     // left >= n，无需删除，直接求和
        LL sum = 0;
        for (int x : nums) sum += x;
        return sum;
    }

    // 用链表模拟循环删除
    list<int> alive(nums.begin(), nums.end());
    auto start = alive.begin();          // 起跳点，初始为索引 0 对应的元素

    // 直到剩下 left 个数
    while (alive.size() > left) {
        auto cur = start;
        auto prev = start;

        // 从起跳点的“下一个”开始走 jump+1 步：
        // 其中前 jump 步是“被跳过”的数字，第 jump+1 步落在“命中点”上
        for (int i = 0; i < jump + 1; ++i) {
            prev = cur;                  // 记录上一个位置（最后一个被跳过的数字）
            ++cur;
            if (cur == alive.end()) {
                cur = alive.begin();     // 环形
            }
        }

        // cur 指向要删除的命中点，prev 指向下一轮的起跳点
        start = prev;
        alive.erase(cur);
    }

    // 计算剩余元素之和
    LL sum = 0;
    for (const auto x : alive) sum += x;
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    getline(cin, line);
    auto nums = parseArray(line);
    int jump, left;
    cin >> jump >> left;

    cout << sumOfLeft(nums, jump, left) << '\n';
    return 0;
}
