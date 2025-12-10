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

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    // c = n / m 向上取整
    int c = (n + m - 1) / m;
    // 初始化矩阵为 *
    vector<vector<string>> a(m, vector<string>(c, "*"));

    // 螺旋矩阵写法
    int top = 0, bottom = m - 1, left = 0, right = c - 1;
    int cur = 1;

    while (top <= bottom && left <= right && cur <= n) {

        // 从左到右
        for (int j = left; j <= right && cur <= n; j++)
            a[top][j] = to_string(cur++);
        top++;

        // 从上到下
        for (int i = top; i <= bottom && cur <= n; i++)
            a[i][right] = to_string(cur++);
        right--;

        // 从右到左
        for (int j = right; j >= left && cur <= n; j--)
            a[bottom][j] = to_string(cur++);
        bottom--;

        // 从下到上
        for (int i = bottom; i >= top && cur <= n; i--)
            a[i][left] = to_string(cur++);
        left++;
    }

    // 输出矩阵
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < c; j++) {
            cout << a[i][j];
            if (j + 1 < c) cout << " ";
        }
        if (i + 1 < m) cout << "\n";
    }

    return 0;
}
