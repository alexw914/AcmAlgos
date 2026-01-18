//
// Created by Krisw on 2026/1/16.
//

/*
给定一个整数数组 nums、一个数字k，一个整数目标值 target，请问nums中是否存在k个元素使得其相加结果为target，请输出所有符合条件且不重复的k元组的个数

数据范围
2 <= nums.length <= 200
-10^9 < numslil < 10^9
-10^9 < target < 10^9
2<=k<=100
输入描述
第一行是nums取值: 2 7 11 15
第二行是k的取值: 2
第三行是target取值: 9
输出描述
输出第一行是符合要求的元组个数: 1补充说明: [2,7]满足，输出个数是1

示例1：

输入

-1 0 1 2 -1 -4

3

0
输出
2
说明
[-1,0,1]，[-1,-1,2]满足条件

这一题int可能会超范围
*/

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

vector<int> parseArray(const std::string &line, char delim) {
    stringstream ss(line);
    string item;
    vector<int> array;
    while (getline(ss, item, delim)) {
        array.push_back(stoi(item));
    }
    return array;
}

vector<int> nums;
int k, target;
int ans = 0;

void backtracking(int curSum, int s, int startIdx) {
    if (s == k) {
        if (curSum == target) {
            ans++;
        }
        return;
    }
    for (int i = startIdx; i < nums.size(); i++) {
        if (i > startIdx && nums[i] == nums[i - 1]) continue; // 关键、去重
        backtracking(nums[i] + curSum, s + 1, i + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    getline(cin, line);
    nums = parseArray(line, ' ');
    cin >> k;
    cin >> target;
    sort(nums.begin(), nums.end());
    backtracking(0, 0, 0);
    cout << ans << endl;

    return 0;
}
