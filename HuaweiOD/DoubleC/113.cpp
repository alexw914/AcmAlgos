//
// Created by Krisw on 2026/1/18.
//

/*
给定一个数组X和正整数K，请找出使表达式X[i] - x[i +1] ... - X[i + K - 1]，结果最接近于数组中位数的下标i，如果有多个i满足条件，请返回最大的i。
其中，数组中位数:长度为N的数组，按照元素的值大小升序排列后，下标为N/2元素的值
补充说明:
1.数组X的元素均为正整数;
2.X的长度n取值范围: 2<= n <= 1000;
3.K大于0且小于数组的大小;
4.i的取值范围: 0 <=i < 1000;
5.题目的排序数组X[N]的中位数是X[N/2].
示例1
输入:
[50,50,2,3],2
输出:

1

说明:
1、中位数为50: [50,50,2,3]升序排序后变成[2,3,50,50]，中位数为下标4/2=2的元素50;

2、计算结果为1: X[50,50,2,3]根据题目计算X[i] - ...- X[i + K- 1]得出三个数

0 (X[0]-X[1]= 50 -50) 、

48 (X[1]-X[2] = 50 -2)

-1 (X[2]-X[3]= 2-3) ，

其中48最接近50，因此返回下标1
*/

#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

vector<int> parseArray(const std::string &line) {
    stringstream ss(line);
    string item;
    vector<int> array;
    while (getline(ss, item, ',')) {
        array.push_back(stoi(item));
    }
    return array;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    getline(cin, line);
    int r = line.size() - 1;
    while (r >= 0 && line[r] != ']') r--;

    auto array = parseArray(line.substr(1, r - 1));
    const int N = array.size();
    int k = stoi(line.substr(r + 2));
    auto sort_array = array;
    sort(sort_array.begin(), sort_array.end());
    int mid = sort_array[N / 2];

    // 前缀和
    vector<int> prefix(N + 1, 0);
    for (int i = 1; i <= N; ++i) {
        prefix[i] = prefix[i-1] + array[i];
    }

    int min_dist = INT_MAX;
    int min_idx = 0;
    for (int i = 0; i + k <= N; i++) {
        auto val = array[i] - (prefix[i + k - 1] - prefix[i]);
        int dist = abs(mid - val);

        if (dist < min_dist || (dist == min_dist && i > min_idx)) {
            min_dist = dist;
            min_idx = i; // 返回最大i
        }
    }

    cout << min_idx << '\n';
    return 0;

}
