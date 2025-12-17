//
// Created by Krisw on 2025/12/16.
//

/*
给定一个矩阵，包含N*M个整数，和一个包含K个整数的数组现在要求在这个矩阵中找一个宽度最小的子矩阵，要求子矩阵包含数组中所有的整数。

输入描述
第一行输入两个正整数N，M，表示矩阵大小。

接下来N行M列表示矩阵内容。下一行包含一个正整数K。下一行包含K个整数，表示所需包含的数组，K个整数可能存在重复数字。

所有输入数据小于1000。

输出描述
输出包含一个整数，表示满足要求子矩阵的最小宽度，若找不到，输出-1

示例1
输入
2 5
1 2 2 3 1
2 3 2 3 2
3
1 2 3
输出
2

说明

矩阵第0、1列包含了1、2、3，矩阵第3、4列包含了1、2、3

示例2
输入

2 5
1 2 2 3 1
1 3 2 3 4
3
1 1 4

输出

5

说明

矩阵第1,2,3,4,5列包含了1,1,4
*/

#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M; // N行 M列
    cin >> N >> M;

    vector<vector<int>> mat(N, vector<int>(M));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            cin >> mat[i][j];

    int K;
    cin >> K;

    const int MAXV = 1000; // 输入数据 < 1000
    vector<int> need(MAXV, 0), have(MAXV, 0);

    int requiredTypes = 0;  // 需要满足的不同数字种类数
    for (int i = 0; i < K; ++i) {
        int x; cin >> x;
        if (need[x] == 0) requiredTypes++;
        need[x]++;
    }

    int satisfied = 0; // 已满足( have[v] >= need[v] )的种类数

    auto addVal = [&](int v) {
        if (need[v] == 0) return;
        have[v]++;
        if (have[v] == need[v]) satisfied++;
    };
    auto removeVal = [&](int v) {
        if (need[v] == 0) return;
        if (have[v] == need[v]) satisfied--;
        have[v]--;
    };

    int ans = 1e9;
    int l = 0;

    for (int r = 0; r < M; ++r) {
        // 加入第 r 列（所有行）
        for (int i = 0; i < N; ++i) addVal(mat[i][r]);

        // 如果满足需求，收缩左边界
        while (l <= r && satisfied == requiredTypes) {
            ans = min(ans, r - l + 1);
            for (int i = 0; i < N; ++i) removeVal(mat[i][l]);
            l++;
        }
    }

    cout << (ans == 1e9 ? -1 : ans) << "\n";
    return 0;
}
