//
// Created by Krisw on 2025/12/17.
//
/*
实现一个简单的绘图模块，绘图模块仅支持矩形的绘制和擦除。

当新绘制的矩形与已有图形重叠时，对图形取并集；
当新擦除的矩形与已有图形重叠时，对图形取差集。
给定一系列绘制和擦除操作，计算最终图形的面积。
输入描述
第一行为操作数N，接下来的N行格式为：

d x1 y1 x2 y2：d表示绘制操作，(x1,y1)为矩形左上角坐标，(x2,y2)为右下角坐标；
e x1 y1 x2 y2：e表示擦除操作，坐标含义同上。
坐标均为整数且范围在[-100, 100]内，用例保证坐标有效性。
输出描述
输出最终图形的面积。

示例1
输入：

2
d 0 2 2 0
d -1 1 1 -1
输出：
7


示例2
输入：

2
d 0 2 2 0
e -1 1 1 -1
输出：
3
*/

#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;

    const int SHIFT = 100; // 把 [-100,100) 平移到 [0,200)
    const int SIZE = 200;

    bool grid[SIZE][SIZE] = {false};

    for (int i = 0; i < N; i++) {
        char op;
        int x1, y1, x2, y2;
        cin >> op >> x1 >> y1 >> x2 >> y2;

        int xL = min(x1, x2);
        int xR = max(x1, x2);
        int yB = min(y1, y2);
        int yT = max(y1, y2);

        for (int x = xL; x < xR; x++) {
            for (int y = yB; y < yT; y++) {
                int gx = x + SHIFT;
                int gy = y + SHIFT;
                grid[gx][gy] = (op == 'd');
            }
        }
    }

    int area = 0;
    for (int x = 0; x < SIZE; x++) {
        for (int y = 0; y < SIZE; y++) {
            if (grid[x][y]) area++;
        }
    }

    cout << area << endl;
    return 0;
}
