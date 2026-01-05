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

#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;

    int c = (n + m - 1) / m;
    vector<vector<string>> a(m, vector<string>(c, "*"));

    int top = 0, bottom = m - 1, left = 0, right = c - 1;
    int cur = 1;

    while (top <= bottom && left <= right && cur <= n) {
        for (int j = left; j <= right && cur <= n; j++)
            a[top][j] = to_string(cur++);
        top++;

        for (int i = top; i <= bottom && cur <= n; i++)
            a[i][right] = to_string(cur++);
        right--;

        for (int j = right; j >= left && cur <= n; j--)
            a[bottom][j] = to_string(cur++);
        bottom--;

        for (int i = bottom; i >= top && cur <= n; i--)
            a[i][left] = to_string(cur++);
        left++;
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < c; j++) {
            cout << a[i][j];
            if (j != c - 1) cout << " ";
        }
        if (i != m - 1) cout << endl;
    }

    return 0;
}
