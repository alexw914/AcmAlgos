//
// Created by Krisw on 2025/12/6.
//
/*
疫情期间，小明隔离在家，百无聊赖，在纸上写数字玩。他发明了一种写法:
给出数字个数n和行数m(1 < n,m < 999)，从左上角的1开始，按照顺时针螺旋向内写方式，依次写出2,3...n,最终形成个一m行矩阵。
小明对这个矩阵有些要求
1.每行数字的个数一样多
2.列的数量尽可能少
3.填充数字时优先填充外部
4.数字不够时，使用单个*号占位
输入描述
输入一行，两个整数，空格隔开，依次表示n、m
输出描述
符合要求的唯一矩阵


示例1：
输入

9 4
输出
1 2 3

* * 4

9 * 5

8 7 6

示例2：
输入
3 5
输出
1

2

3

*

*
 */
#include <bits/stdc++.h>
using namespace std;


int dfs(vector<vector<int>>& matrix, vector<vector<bool>>& vis, int x) {

}


int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int c = (n + m - 1) / m;
    vector<vector<int>> Matrix(m, vector<int>(n, 0));
    vector<vector<bool>> vis(m, vector<bool>(n, false));
    int step;
    while (step < m * n) {

    }




    return 0;
}
