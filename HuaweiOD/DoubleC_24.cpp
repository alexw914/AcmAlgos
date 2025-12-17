//
// Created by Krisw on 2025/12/17.
//

/*
【补种未成活胡杨】

近些年来，我国防沙治沙取得显著成果。某沙漠新种植N棵胡杨（编号1-N），排成一排。

一个月后，有M棵胡杨未能成活。

现可补种胡杨K棵，请问如何补种（只能补种，不能新种），可以得到最多的连续胡杨树？

输入描述

N 总种植数量

M 未成活胡杨数量

M 个空格分隔的数，按编号从小到大排列

K 最多可以补种的数量

其中：

1 <= N <= 100000

1 <= M <= N

0 <= K <= M

输出描述

最多的连续胡杨棵树

示例1  输入输出示例仅供调试，后台判题数据一般不包含示例

输入

5

2

2 4

1

输出

3

说明

补种到2或4结果一样，最多的连续胡杨棵树都是3。

示例2
输入
10
3
2 4 7
1
输出
6
说明
补种第7棵树，最多的连续胡杨棵树为6(5,6,7,8,9,10)
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M, K;
    cin >> N;
    cin >> M;
    unordered_map<int, int> deadMp;
    while (M--) {
        int x;
        cin >> x;
        deadMp[x]++;
    }
    cin >> K;

    int i = 1, j = 1;
    int cnt = 0;
    int ans = 0;
    while (j <= N) {
        if (deadMp.count(j)) cnt++;
        j++;

        while (cnt > K) {
            if (deadMp.count(i)) cnt--;
            i++;
        }
        ans = max(ans, j - i); // 窗口是 [i, j)
    }
    cout << ans << endl;
    return 0;
}
