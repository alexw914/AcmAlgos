//
// Created by Krisw on 2025/12/11.
//

/*
给定两个字符串，分别为字符串A与字符串B。例如A字符串为ABCABBA，B字符串为CBABAC。可以得到m*n的二维数组，定义原点为(0,0)，终点为(m,n)，
水平与垂直的每一条边距离为1,从原点(0,0)到(0,A)为水平边，距离为1，从(0,A)到(A,C)为垂直边，距离为1;
假设两个字符串同一位置的两个字符相同则可以作一个斜边、如(A.C)到.B)最短距离为斜边，距离同样为1。作出所有的斜边，
则有(0.0)到(B.B)的距离为 1个水平边+1个垂直边+1个斜边 =3。
根据定义可知，原点到终点的最短距离路径如下图红线标记，最短距离为9;

路径为(0,0)->(A,0)->(A,C)->(B,B)->(C,B)->(A,A)->(B,B)->(B,B)->(A,A)->(A,C)


输入描述
空格分割的两个字符串A与字符串B，字符串不为”空串”。

字符格式满足正则规则:[A-Z] 字符串长度<= 10000
输出描述
原点到终点的最短距离

示例1：

输入：

ABC ABC

输出：
3

示例2：

输入：

ABCABBA CBABAC

输出：
9

编辑距离
https://leetcode.cn/problems/edit-distance/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string A, B;
    cin >> A >> B;
    const int M = A.length();
    const int N = B.length();

    // dp[r][c] 为从原点到（r,c）点的最短距离
    vector<vector<int>> dp(M + 1, vector<int>(N + 1, INT_MAX));
    dp[0][0] = 0;

    for (int r = 0; r < M; r++)
        dp[r + 1][0] = dp[r][0] + 1;

    for (int c = 0; c < N; c++)
        dp[0][c + 1] = dp[0][c] + 1;

    for (int r = 0; r < M; r++) {
        for (int c = 0; c < N; c++) {
            // 来自从左侧或上侧
            dp[r + 1][c + 1] = min(dp[r][c + 1], dp[r + 1][c]) + 1;
            if (A[r] == B[c]) {  // 来自从左上角
                dp[r + 1][c + 1] = min(dp[r + 1][c + 1], dp[r][c] + 1);
            }
        }
    }

    cout << dp[M][N] << endl;

    return 0;
}

